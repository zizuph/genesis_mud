/*
 *  Vampire Scry
 *
 *  For spell effect description, see doc/scry.txt
 *
 *  Created May 2008, by Novo
 *  Modified February 2009 to use Genesis Library's scry
 *  Modified April 2009 to fix typo in message and also to make the
 *                      failure message look different than the success
 *                      message.
 *  Modified October 2009 to change config_scry_spell return value and
 *                      parameters. The global config_spell was changed
 *                      to remove unnecessary argument passing.
 */
#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/scry";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include "/d/Terel/guilds/vamp/spells/blood_spell.h"

public object *
target_one_tasted_target(object actor, string str);

/*
 * A number of changes were made to the spell February 2009.
 * The spell was converted to use the new Genesis generic scry as the
 * base spell.
 * Rationale:
 *  A standard scry effect will be added to the ability library, which
 *  will then be used by the Vampire Scry spell. It will no longer be
 *  something that can be cast while on the move. It will also always
 *  alert the target who was scried. All simple scry spells in the game
 *  will be converted to use this central (yet customizable) code.
 *
 */
public void
config_scry_spell()
{
    config_blood_spell();
    
    set_spell_name("scry");
    set_spell_desc("Locate someone");
    set_spell_target(target_one_tasted_target);

    // Generic Spell Settings
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_DIVINATION, 40);
    set_ability_target_verify(0);
    set_spell_vocal(0);
    // Centralized Spell settings
    set_spell_mana_factor(0.74);
    set_spell_time_factor(0.50);
    
    // Blood Spell Specific Settings
    set_blood_cost(11);
    set_min_guild_stat(70);
}


/*
 * Function name: resolve_scry_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_scry_spell(object caster, object *targets, int *resist, int result)
{
    object target = targets[0];

    // This makes our scry target the most recently remembered snack.
    string * names=caster->query_known_scries();
    names-=({ target->query_real_name() });
    names+=({ target->query_real_name() });
    caster->set_known_scries(names);
}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object actor, mixed * targets, 
                   string arg,int execute = 0)
{
    object target;
    
    if (actor->query_bloodguard() && !actor->query_master())
    {
        actor->catch_tell("Without a master, your connection to the "+
        "gift is too weak to perform this.\n");
        return 0;
    }

    target = targets[0];
    // Right before executing, check this
    if (target->query_sire()==actor->query_real_name() || 
        actor->query_sire()==target->query_real_name())
    {
        actor->catch_tell("Try as you might, you cannot see into that "
            + "mind.\n");
        return 0;
    }

    return ::check_valid_action(actor,targets,arg,execute);
}

/*
 * Function name: target_one_tasted_target
 * Description:   Target an ability on living tasted by the actor
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
target_one_tasted_target(object actor, string str)
{
    object living;
    object * tasted;
    
    if (!strlen(str))
    {
        actor->catch_tell("Who have you tasted that you wish "+
            "to locate?\n");
        return ({});
    }

    tasted = actor->query_available_scry_targets();
    if (!sizeof(tasted))
    {
        actor->catch_tell("You cannot recall such a taste.\n");
        return ({ });
    }
    
    object target;
    if (parse_command(str,actor->query_available_scry_targets()
        ,"%o",target))
    {
        return ({ target });
    }
    if (actor->query_met(str))
    {
        actor->catch_tell(CAP(LANG_POSS(str))+" blood feels too "+
            "remote to sense at this time.\n");
    }
    else
    {
        actor->catch_tell("You cannot recall such a taste.\n");
    }
	return ({ });
}

// HOOKS TO BE DEFINED

/*
 * Function:    hook_no_scry_message
 * Description: When it is not possible to scry, for whatever reason,
 *              this message is given. This applies to no-scry properties
 *              as well as trying to scry a wizard.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_no_scry_message(object caster, object target)
{
    caster->catch_tell("Your mind is blocked from watching " 
        + target->query_objective() + " from afar.\n");
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
    caster->catch_tell("Pressing into the mind of " 
        + capitalize(target->query_real_name()) 
        + " you can see through " + POSS(target) + " eyes:\n");
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
    caster->catch_tell("You gaze out through the eyes of your target, but "
        + "see the same as them - nothing.\n");    
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
    caster->catch_tell("You attempt to penetrate the mind of your target, "
        + "but cannot.\n");    
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
    target->catch_msg("You sense a presence in your thoughts.\n");
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
    target->catch_msg("You sense a presence attempting to enter your "
        + "thoughts.\n");
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
query_provide_brief_description(object caster, object * targets, int * resist, int result)
{
    // Never provide a brief description
    return 0;
}
