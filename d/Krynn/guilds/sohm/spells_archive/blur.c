/*
 * Blur spell for SoHM
 * 
 * Created by Arman 2016, based on base evade spell.
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/evade";

/*
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells. Redefine this in your
 *              own stoneskin spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_evade_spell()
{
    set_spell_name("kadenadon");
    set_spell_desc("Blur - caster appears blurred, shifting and wavering.");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_combat_aid(72.0);
    set_spell_can_be_renewed(1);
    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_WATER, 50);
    set_spell_form(SS_FORM_ILLUSION, 50);
    set_spell_task(TASK_HARD);    

    // Can only cast blur on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "blur_obj");
}

/*
 * Function:    query_evade_ingredients
 * Description: This function defines what components are required for
 *              this evade spell.
 */
public string *
query_evade_ingredients(object caster)
{
    return ({"vallenwood blossom", "cattail" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only cast blur on yourself!\n");
        return 0;
    }

    /*  Can't cast spell if using another defensive spell with high C.aid   */

    if("/d/Krynn/guilds/sohm/spells/stoneskin"->has_spell_object(caster))
    {
        caster->catch_tell("Your stoneskin spell interferes with your ability " +
              "to cast the blur spell.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/portents_and_omens"->has_spell_object(caster))
    {
        caster->catch_tell("Your portents and omens spell interferes with your ability " +
              "to cast the blur spell.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/magic_shield"->has_spell_object(caster))
    {
        caster->catch_tell("Your magic shield spell interferes with your ability " +
              "to cast the blur spell.\n");
	return 0; 
    }

    object * effects = caster->query_prop("_live_o_maintained_effects");
    string caster_name = caster->query_real_name();

    foreach (object effect : effects)
    {
        if (objectp(effect))
        {
           if (environment(effect)->query_prop("_sohm_retributive_ward_effect") == caster_name)
           {
                caster->catch_tell("The retributive ward you are maintaining interferes " +
                                   "with your ability to cast blur.\n");
                return 0;
           }
        }
    }
        
    return 1;
}

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"kadenadon_memorised");
}

// HOOKS TO BE DEFINED

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;

        caster_message = "You whirl your arms swiftly through the air, reciting "+
           "magical words of deception and confusion - 'Kaden Adon!' - " +
           "drawing energy to blur your form with a powerful illusion.\n";
        watcher_message = QCTNAME(caster) + " whirls " +caster->query_possessive()+
           " arms swiftly around in a confusingly intricate pattern while " +
           "reciting mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

/*
 * Function:    resolve_evade_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_evade_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already protected by the blur illusion!\n");
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You need a cattail and a vallenwood blossom herb to blur your " +
          "appearance and make yourself harder to hit.\n");
}

