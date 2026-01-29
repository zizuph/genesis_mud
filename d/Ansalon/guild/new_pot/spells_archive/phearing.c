/*
 * pHearing
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/shadow";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"

inherit GUILDDIRSPELL + "common";

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <files.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int
query_spell_level(void)
{
    return 3;
}

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 */
public void
config_shadow_spell(void)
{
    set_spell_name("phearing");
    set_spell_desc("True hearing");

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 14);
    set_spell_form(SS_FORM_ENCHANTMENT, 20);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("Your prayer is unheard.\n");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Can only cast strength on themself
    set_spell_target(spell_target_caster);
   
    set_shadow_filename(HEARING_OBJ);
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_shadow_ingredients(object caster)
{
    return ({ "ear", "cattail" });
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

/*
 * Function meant to be overriden to provide the duration of the weapon
 * effects provided by the shadow.
 */
public float
query_duration_time(void)
{
    // 20 minutes
    return 1200.0;
}

public void
hook_use_ingredients(object *ingrs)
{
    int i = 1;

    if (IS_LEFTOVER_OBJECT(ingrs[0]))
	i = 0;

    write("The " + ingrs[i]->query_race() + " ear bursts " +
	"into a brilliant light before fading into nothingness " +
	"while " + LANG_THESHORT(ingrs[!i]) + " withers away.\n");
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