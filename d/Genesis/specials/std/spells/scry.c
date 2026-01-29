/*
 * Standard Scry Spell for the Genesis Centralized Library
 * 
 * This spell should be the base of any "quick" scry spell. "Quick"
 * scry spells are defined as scry spells that does a snapshot look
 * of the target's room.
 *
 *  Created by Petros, February 2009
 *
 *  Oct 2021 Zizuph - reordered scry to test for immunity on the
 *    player before the room.  Otherwise information leaks out.
 *
 */
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"


// To configure a scry spell, simply define the prototypes. For an
// explanation of their usage, see the header comments above the
// function definition.
public void hook_no_scry_message(object caster, object target);
public void hook_scry_success(object caster, object target, int brief);
public void hook_scry_target_cannot_see(object caster, object target);
public void hook_scry_failure(object caster, object target);
public void hook_notify_been_scried_success(object caster, object target);
public void hook_notify_been_scried_failure(object caster, object target);
public void hook_scry_force_fail(object caster, object *targets, int *resist, int result);
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
    set_spell_peaceful(1);
    set_spell_stationary(1);
}

/*
 * Function name: target_one_distant_living
 * Description:   Target an ability on a living in the game 
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
target_one_distant_living(object actor, string str)
{
    object target;
    if (!strlen(str))
    {
        actor->catch_tell("Target whom?\n");
        return ({ });
    }

    str = lower_case(str);
    target = find_living(str);

// Masking target_one_distant_living to include targeting of npcs

    if (!objectp(target) || target->query_npc() ||
        (target->query_wiz_level() && target->query_invis()))
    { 
	actor->catch_tell("You do not sense " + capitalize(LANG_POSS(str)) +
            " presence in the realms.\n");
	return ({ });
    }

    return ({ target });     
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("scry");
    set_spell_desc("Locate someone");
    set_spell_target(spell_target_one_distant_living);

    set_spell_mana(100);
    set_spell_task(TASK_ROUTINE);
    set_spell_vocal(1);
    set_spell_time(10);
    set_spell_ingredients(query_scry_ingredients);
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

    /*
     * The resolve_scry_spell function has been removed to accomodate greater
     * optionality without changing anything major (which would require changes
     * to all the spells). If you dont want to force a failure, you can just
     * use:
     * 
     * public void resolve_scry_spell(object caster, object *targets,
     *                                int *resist, int result);
     *
     * Using an integer/status/mixed/string, returning a non-null value would
     * result in a forced failure.
     */
    if (this_object()->resolve_scry_spell(caster, targets, resist, result))
        return hook_scry_force_fail(caster, targets, resist, result);
    
    if (target == caster)
    {
        caster->do_glance();
        return;
    }

    if (target->query_npc())
    {
        // Not allowed to scry npcs
        hook_no_scry_message(caster, target);
        return;
    }
    
    if (target->query_wiz_level()
        || target->query_linkdead())
    {
        // Not allowed to scry wizards or linkdead people
        hook_no_scry_message(caster, target);
        return;
    }
    
    target_room = environment(target);

    // If it's not a valid room, fail.
    if (!objectp(target_room))
    {
        hook_scry_failure(caster, target);
        hook_notify_been_scried_failure(caster, target);
        return;
    }

    // If the target is no scry, fail.
    no_scry = target->query_prop(LIVE_M_NO_SCRY);
    if (no_scry)
    {
        if (stringp(no_scry))
        {      
            // If the property specified its own no scry message, we
            // use that instead.
            caster->catch_tell(no_scry + "\n");
        }
        else
        {
            hook_no_scry_message(caster, target);
        }
        return;
    }

    // If the room is no scry, fail.
    no_scry = target_room->query_prop(ROOM_M_NO_SCRY);
    if (no_scry)
    {
        if (stringp(no_scry))
        {      
            // If the room specified its own message, we use that
            // instead.
            caster->catch_tell(no_scry + "\n");
        }
        else
        {
            hook_no_scry_message(caster, target);
        }
        return;
    }

    // Test to see whether the scry passes the resistance of the target
    if (resist[0] > random(100))
    {
        hook_scry_failure(caster, target);
        hook_notify_been_scried_failure(caster, target);
        return;
    }        

    hook_notify_been_scried_success(caster, target);
    
    if (!CAN_SEE_IN_ROOM(target))
    {
        hook_scry_target_cannot_see(caster, target);
        return;
    }
    
    
    if (query_provide_brief_description(caster, targets, resist, result))
    {
        hook_scry_success(caster, target, 1);
	    caster->catch_tell(capitalize(target_room->short()) + ".\n");
	    caster->catch_tell(target_room->exits_description());
	}
	else
    {
        hook_scry_success(caster, target, 0);
        caster->catch_tell(capitalize(target_room->short()) + ".\n");
	    caster->catch_tell(target_room->long());
    }

    object * inv = all_inventory(environment(target)) - ({ target });
    inv=filter(inv, &->check_seen(target));
    
    object * live = FILTER_LIVE(inv);
    object * dead = FILTER_DEAD(inv);
    
    if (sizeof(dead))
    {
        caster->catch_msg(capitalize(COMPOSITE_DEAD(dead))+".\n");
    }
    if (sizeof(live))
    {
        caster->catch_msg(capitalize(COMPOSITE_LIVE(live))+".\n");
    }
}

// HOOKS TO BE DEFINED

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
 * Function name:   hook_notify_been_scried_failure
 * Description:     A hook added in case of forced failure of the spell. The
 *                  forced failure was added to further be able to customize
 *                  the spell.
 * Arguments:       (object)   caster  - the caster
 *                  (object *) targets - an array of targets
 *                  (int *)    resist  - resistance percentages corresponding to
 *                                       each target
 *                  (int)      result  - how well the spell was cast
 * Returns:         Nothing
 */
public void
hook_scry_force_fail(object caster, object *targets, int *resist, int result)
{
} /* hook_scry_force_fail*/

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
query_provide_brief_description(object caster, object * targets, int * resist, int result)
{
    // 50% chance of getting a brief description
    return random(2);
}
