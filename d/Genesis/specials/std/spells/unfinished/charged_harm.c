/*
 * Generic Charged Harm Spell
 *
 * This charged harm spell introduces a new type of harm spell into the
 * game. Up until this was implemented, we had just instant harm
 * and at-will harm.
 *
 * A charged harm spell is unique in that you cast it into a maintained
 * spell. Once you have the maintained spell object, the object continually
 * "charges" up. You can choose to release the charge at any time to
 * trigger the harm effects.
 * 
 * Inherit this and reconfigure it for your own charged harm.
 *
 * Created by Petros, July 2016
 */
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_harm_spell(object caster, object *targets, int *resist, int result);
public void hook_already_has_spell_object(object caster, object target);

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 */
public void
config_harm_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(100.0);
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_offensive(1);    
}


/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({  });
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("harm");
    set_spell_desc("Harm someone");
    set_spell_target(spell_target_one_other_present_living_or_enemy);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_ingredients(query_harm_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each harm spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
        
    // Call the specific configuration that is to be masked.
    config_harm_spell();
    
    // Call this after the config_harm_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    if (!query_spell_can_be_renewed())
    {
        // This spell cannot be cast again if it is already in effect
        foreach (object target : targets)
        {
            if (has_spell_object(target))
            {
                hook_already_has_spell_object(caster, target);
                return 0;
            }
        }
    }
        
    return result;    
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, object * targets, int * resist, int result)
{
    resolve_harm_spell(caster, targets, resist, result);

    mapping spell_input = ([ ]);
    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    spell_input["targets"] = targets;
    spell_input["aid"] = query_spell_combat_aid();
    // The caster is the actual "target" where the spell object will reside
    make_spell_object(query_spell_object(), caster, caster, resist, result, spell_input);
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Called whenever the caster tries to cast this spell again when
 *              it is already in effect.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    write("You already have a charged harm in effect!\n");
}
