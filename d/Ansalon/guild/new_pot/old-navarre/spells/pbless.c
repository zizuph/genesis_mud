/*
 * pBless - this spell offers protection to the Priest against all forces that
 *          go against Takhisis will.
 *          It is a stoneskin type spell.
 * Navarre: March 2013.
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/stoneskin";
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "../defs.h"
#include "../std/generic_functions.c"
#include "/d/Ansalon/common/defs.h"

// Prototypes
public void resolve_stoneskin_spell(object caster, mixed* targets,
                                    int* resist, int result);
private object resolve_one_target(object caster, mixed* targets);


/*
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stoneskin_spell()
{
    set_spell_name("pbless");
    set_spell_desc("Invoke the Dark Queen's blessing");
  //  set_spell_time(6);
  //  set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 25);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(spell_target_one_present_living);
    set_spell_vocal(1);
    set_spell_peaceful(0);
    set_spell_stationary(1);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_combat_aid(50.0);

    // Spell effect object
    set_spell_object(POT_SPELL_OBJS +  "pbless_obj");
}

/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string*
query_stoneskin_ingredients(object caster)
{
    return ({"onoclea"});
}


/*
 * Function:    resolve_stoneskin_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stoneskin_spell(object caster, mixed* targets, int* resist,
                        int result)
{
    object target = resolve_one_target(caster, targets);
    
    if (caster == target)
    {
        caster->catch_tell("You invoke Takhisis' blessing against her " +
                           "enemies. You feel a warm touch over " +
                           "your body and you know you are less " +
                           "vulnerable to attacks.\n");
                               
        my_tell_roombb(environment(caster), QCTNAME(caster) + " blesses " +
                       HIM(caster) + "self in the name of Takhisis, " +
                       "Queen of Darkness.\n", caster);
        }
        else
        {
            caster->catch_tell("You bless " + target->query_the_name(caster) + 
                               " in the name of Takhisis, Queen of " +
                               "Darkness.\n");

            target->catch_tell(caster->query_The_name(target) + " blesses you in " +
                            "the name of Takhisis, Queen of Darkness. You " +
                            "feel a warm touch over your body and you know " +
                            "you are less vulnerable to attacks.\n");

            my_tell_roombb(environment(caster), QCTNAME(caster) + " blesses " +
                           QTNAME(target) + " in the name of Takhisis, Queen of " +
                           "Darkness.\n", caster, ({target}));
        }
}

/**
 * Helper function to perform validation checks and retrieve target.
 */
private object
resolve_one_target(object caster, mixed* targets)
{
    int number_of_targets = sizeof(targets);
    object target = 0;
    
    // Safety check
    if (!number_of_targets)
    {
        caster->catch_tell("No valid targets found!\n");    
    }
    else if (number_of_targets > 1)  // This should never happen
    {
        caster->catch_tell("Error: Please report that multiple players " +
                           "were accepted as target at the same time.\n");
    }
    else
    {
        target = targets[0];
    }
    return target;    
}


public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        caster->catch_tell("You are already blessed by Takhisis, and " +
    	                   "the prayer has no effect.\n");
    }
    else
    {
        caster->catch_tell(target->query_The_name(caster) + " is already " +
                           "blessed, so the spell has no effect.\n");
    }
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already
existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed* targets)
{
    object target = resolve_one_target(caster, targets);
        
    if (caster == target)
    {
        
        caster->catch_tell("You call upon Takhisis to reinforce the " +
                           "blessing against her enemies.\n");
                               
        my_tell_roombb(environment(caster), QCTNAME(caster) + " blesses " +
                       HIM(caster) + "self in the name of Takhisis, " +
                       "Queen of Darkness.\n", caster);
    }
    else
    {
        caster->catch_tell("You reinforce the blessing of Takhisis, Queen " +
                           "of Darkness, upon " +
                           target->query_the_name(caster) + ".\n");
        
        target->catch_tell(caster->query_The_name(target) + " reinforces the " +
                        "blessing of Takhisis, Queen of Darkness, upon " +
                        "you.\n");

        my_tell_roombb(environment(caster), QCTNAME(caster) + " blesses " +
                       QTNAME(target) + " in the name of Takhisis, Queen of " +
                       "Darkness.\n", caster, ({target}));
    }
}

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 9;
}
