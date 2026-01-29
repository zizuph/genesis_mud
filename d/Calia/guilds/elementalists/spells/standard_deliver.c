/*
 * Deliver Spell for the Genesis Centralized Library
 * 
 * This spell should be the base of any deliver spell. It is 
 * based off the standard scry spell coded by Petros, February 2009.
 *
 */
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"


// To configure a scry spell, simply define the prototypes. For an
// explanation of their usage, see the header comments above the
// function definition.
public void resolve_scry_spell(object caster, object *targets, int *resist, int result);
public void hook_no_scry_message(object caster, object target);
public void hook_scry_success(object caster, object target, int brief);
public void hook_scry_target_cannot_see(object caster, object target);
public void hook_scry_failure(object caster, object target);
public void hook_notify_been_scried_success(object caster, object target);
public void hook_notify_been_scried_failure(object caster, object target);
public int  query_provide_brief_description(object caster, object * targets, int * resist, int result);

/*
 * Function:    query_scry_ingredients
 * Description: This function defines what components are required for
 *              this scry spell.
 */
public string *
query_scry_ingredients(object caster)
{
    // Default requirements to be listed ...
    return ({ "sargassum" });
}

/*
 * Function:    config_scry_spell
 * Description: Config function for scry spells. Redefine this in your
 *              own scry spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_scry_spell()
{
    // Nothing special here.
}

private nomask void
config_required_parameters()
{
    // By default, all scry spells must be peaceful and stationary
    set_spell_stationary(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("scry");
    set_spell_desc("Locate someone");
    set_spell_target(spell_target_one_distant_known_living);

    set_spell_mana(40);
    set_spell_task(TASK_ROUTINE);
    set_spell_vocal(1);
    set_spell_time(6);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(0);
    
    // We set defaults for the spell element and form here. Scrying
    // involves divination, so that's a no brainer. We randomly chose
    // life here as it relates most to what you are divining.
    // Each scry spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 30);
    set_spell_form(SS_FORM_DIVINATION, 40);
        
    // Call the specific configuration that is to be masked.
    config_scry_spell();
    
    // Call this after the config_scry_spell to ensure that
    // scry spells are always peaceful and stationary.
    config_required_parameters();
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
resolve_spell(object caster, object *targets, int *resist, int result)
{ 
    object target = targets[0];
    object target_room;
    mixed no_scry;        

    resolve_scry_spell(caster, targets, resist, result);
   
    if (target->query_wiz_level()
        || target->query_linkdead())
    {
        // Not allowed to scry wizards or linkdead people
        hook_no_scry_message(caster, target);
        return;
    }

    hook_scry_success(caster, target, 1);
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_scry_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_scry_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function:    hook_no_scry_message
 * Description: When it is not possible to scry, for whatever reason,
 *              this message is given. This applies to no-scry properties
 *              as well as trying to scry a wizard or someone linkdead.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_no_scry_message(object caster, object target)
{
    caster->catch_tell("You sense only a blank as you attempt to "
        + "divine the location of your target.\n");    
}

/*
 * Function:    hook_scry_success
 * Description: When there is a successful scry, a message is prepended
 *              before the room descriptions. This is where you
 *              customize that message.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 *              brief  - whether the description will be brief or not
 */
public void
hook_scry_success(object caster, object target, int brief)
{
    if (brief)
    {
        caster->catch_tell("You vaguely sense your target's surroundings "
            + "as through their perceptions.\n");
    }
    else
    {
        caster->catch_tell("You see your target's surroundings, as "
            + "through their eyes.\n");
    }
}

/*
 * Function:    hook_scry_target_cannot_see
 * Description: When the scry target cannot see, the person scrying also
 *              sees a dark room. One can customize this message here.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_scry_target_cannot_see(object caster, object target)
{
    caster->catch_tell("A dark room.\n");
}

/*
 * Function:    hook_scry_failure
 * Description: When the scry fails because of resistance failure, this
 *              message is given. Also given when the target room doesn't
 *              exist.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_scry_failure(object caster, object target)
{
    caster->catch_tell("You attempt to divine the location of your "
        + "target, but something prevents you from doing so.\n");    
}

/*
 * Function:    hook_notify_been_scried_success
 * Description: A person being scried is notified whenever they are scried.
 *              This message is the one that indicates to them that
 *              the scry was successful.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_notify_been_scried_success(object caster, object target)
{
    target->catch_tell("You sense an intruding presence in your "
        + "mind.\n");
}

/*
 * Function:    hook_notify_been_scried_failure
 * Description: A person being scried is notified whenever they are scried.
 *              This message is the one that indicates to them that
 *              the scry was not successful.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_notify_been_scried_failure(object caster, object target)
{
    target->catch_tell("You sense someone trying to invade your mind, "
        + "but you successfully ward off the intruding presence.\n");
}

/*
 * Function:    query_provide_brief_description
 * Description: Sometimes scrying should not show the full description.
 *              Instead, it will only show the brief description of
 *              the room. This function determines whether it is brief
 *              or not. By default, it's a 50% chance of it being brief.
 *              You should customize it to suit your needs.
 * Arguments:   same as config_spell
 */
public int
query_provide_brief_description(object caster, object * targets, 
	int * resist, int result)
{
    // 50% chance of getting a brief description
    return random(2);
}
