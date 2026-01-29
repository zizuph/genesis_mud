/*
 * Shadowblink spell used in Kalad, based on the standard
 * blink spell.
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/blink";
#include "defs.h"
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>


/*
 * Function:    config_blink_spell
 * Description: Config function for blink spells. Redefine this in your
 *              own blink spells to override the defaults.
 */
public void
config_blink_spell()
{
    set_spell_name("shadowblink");
    set_spell_desc("dark shadows surrounding");

    set_spell_task(TASK_ROUTINE);
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Can only cast blink on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(SPELL_DIR + "obj/shadowblink_obj");

}

/*
 * Function   : query_blink_ingredients
 * Description: This function defines what components are required for
 *              this blink spell.
 * Arguments  : object caster
 * Returns    : a string * with the required regents.
 */
public string *
query_blink_ingredients(object caster)
{
    return ({ "" });
}

/*
 * Function   : check_valid_action
 * Description: checks if its a valid action
 * Arguments  : object caster, mixed * targets, string arg, int execute
 * Returns    : 1 success 0 fail
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;
   
    return 1;
}

/*
 * Function   : hook_already_has_spell_object
 * Description: checks if the spell is already active
 * Arguments  : object caster, object target
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        write("You are already surrounded by dark shadows.\n");
    }
    else
    {
        caster->catch_msg("You are already surrounded by dark shadows.\n");
    }
}

/*
 * Function name: hook_no_ingredients_fail
 * Description  : Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Arguments    : a * with the needed components
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You are missing an ingredient to cast that spell!\n");
}

/*
 * Function   : query_blink_interval
 * Description: Sets how often the spell should trigger
 * Returns    : The time in seconds on how often it should trigger
 */
public float
query_blink_interval()
{
    return 1.0; // set default blink interval to 1 seconds.
}

