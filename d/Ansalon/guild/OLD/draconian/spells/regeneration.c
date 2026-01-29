/*
 * General Regeneration Spell
 * 
 * This is a generic regeneration spell that should be used as the basis for all
 * mage armour spells under the Genesis Magic system created in 2009. It 
 *
 * Created by Petros, September 2009
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "/d/Genesis/specials/std/spells/defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_regeneration_spell(object caster, mixed * targets, int * resist, int result);

/*
 * Function:    config_regeneration_spell
 * Description: Config function for regeneration spells. Redefine this in your
 *              own regeneration spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_regeneration_spell()
{
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_combat_aid(25.0);

    // Spell effect object
    set_spell_object(STD_SPELL_OBJ_DIR + "regeneration_obj");
}

/*
 * Function:    query_regeneration_ingredients
 * Description: This function defines what components are required for
 *              this regeneration spell.
 */
public string *
query_regeneration_ingredients(object caster)
{
    // Onyx gem provides the "earth" element. Chicory provides the
    // constitution (fatigue) generating factor.
    return ({ });
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    if (query_spell_combat_aid() > 25.0)
    {
        // We don't allow combat aid to exceed 25% for regeneration spells.
        // Even at 25%, it means approximately 400 hp healed in a minute. Only
        // the most advanced of caster guilds should get this.
        // As a comparison, skunk berries typically provide about a 4% combat
        // aid, which give it about 60 hp per minute regeneration. The maximum
        // regeneration capability will equal a person who has consumed 6-7
        // skunk berries.
        set_spell_combat_aid(25.0);
    }
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("regeneration");
    set_spell_desc("Hasten metabolic healing");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_regeneration_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_WATER, 25);
    set_spell_form(SS_FORM_TRANSMUTATION, 25);
        
    // Call the specific configuration that is to be masked.
    config_regeneration_spell();
    
    // Call this after the config_regeneration_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_regeneration_spell(caster, targets, resist, result);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    float aid = query_spell_combat_aid(); // effect uses combat aid
    make_spell_object(query_spell_object(), caster, targets, resist, result, aid);
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
    
    // The regeneration spell cannot be cast if it is already in effect
    foreach (object target : targets)
    {
        if (has_spell_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }
    }
    
    return result;    
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_regeneration_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_regeneration_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You metabolism is already in overdrive!\n");
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        "onyx shard, chicory"));
}
