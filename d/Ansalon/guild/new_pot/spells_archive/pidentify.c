/*
 * pIdentify
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/identify";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"
#include "/d/Ansalon/common/defs.h"

inherit GUILDDIRSPELL + "common";

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <language.h>
#include <wa_types.h>



/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int
query_spell_level(void)
{
    return 9;
}

/*
 * Function:    config_identify_spell
 * Description: Config function for identify spells. Redefine this in your
 *              own identify spells to override the defaults.
 */
public void
config_identify_spell(void)
{
    set_spell_name("pidentify");
    set_spell_desc("Identify a magic item");

    set_spell_element(SS_ELEMENT_LIFE, 14);
    set_spell_form(SS_FORM_DIVINATION, 24);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("Your prayer is unheard.\n");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
}

/*
 * Function:    query_identify_ingredients
 * Description: This function defines what components are required for
 *              this identify spell.
 */
public string *
query_identify_ingredients(object caster)
{
    return ({ "pearl" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);

    return 1;
}

public void
hook_use_ingredients(object *ingrs)
{
     write(C(LANG_THESHORT(ingrs[0])) + " cracks into small shards " +
           "and slips through your " +
           (objectp(this_player()->query_armour(A_HANDS)) ? "gloved " :
           "") + "fingers.\n");
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id(MEDALLION_ID))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(caster,));

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!med[0]->query_worn())
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    if (ret)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
        
    return ret;
}