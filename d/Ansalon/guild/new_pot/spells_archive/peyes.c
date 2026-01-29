/*
 * pEyes
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/darkvision";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit GUILDDIRSPELL + "common";

#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int
query_spell_level(void)
{
    return 5;
}

/*
 * Function:    config_darkvision_spell
 * Description: Config function for darkvision spells. Redefine this in your
 *              own darkvision spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_darkvision_spell(void)
{
    set_spell_name("peyes");
    set_spell_desc("Give yourself the vision of a dragon");

    set_spell_element(SS_ELEMENT_LIFE,  45);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("Your prayer is unheard.\n");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0); 
    set_spell_offensive(0);

    // Can cast peyes on others if in Aspect of the Lady
    set_spell_target(spell_target_one_present_living);

    // Set the effect object filename
    set_spell_object(EYES_OBJ);
}

/*
 * Function:    query_darkvision_ingredients
 * Description: This function defines what components are required for
 *              this dark vision spell.
 */
public string *
query_darkvision_ingredients(object caster)
{
    return ({ "eye", "eye"});
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

    if(!caster->query_prop(DARK_LADY_ASPECT) && (targets[0] != caster))
    {
        caster->catch_tell("You can only cast this prayer on others when " +
            "under the aspect of the Dark Lady.\n");
        return 0;
    }

    return 1;
}

public void
hook_use_ingredients(object *ingrs)
{
    string *arr = ingrs->query_race();

    if (arr[0] == arr[1])
        arr = arr[1..];

    write("The pair of " + COMPOSITE_WORDS(arr) + " eyes " +
        "glow briefly, their pupils changing to reptilian, before " +
        "they are consumed.\n");
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