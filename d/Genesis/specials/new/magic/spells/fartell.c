/*
 * General Tell Spell
 * 
 * This is a generic tell spell that should be used as the basis for all
 * tell spells under the Genesis Magic system created in 2009.
 *
 * Created by Petros, September 2009
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>

#include "defs.h"
inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Global Variables
public int      Fartell_unmet;

// Prototypes
public void resolve_fartell_spell(object caster, mixed * targets, int * resist, int result);
public nomask mixed * target_fartell_spell(object caster, string str);
public int  is_valid_fartell_target(object caster, object target);
public void hook_fartell_no_target(object caster);
public void hook_fartell_self(object caster);
public void hook_fartell_no_message(object caster);
public void hook_fartell_target_unavailable(object caster, string target);
public void hook_fartell_target_not_valid(object caster, string target);
public void hook_fartell_target_unmet(object caster, string target);
public void hook_send_gmcp_comms(object caster, object target, string message_text);
public void hook_do_fartell_spell(object caster, object target, string message_text);
public string * query_fartell_ingredients(object caster);

/*
 * Function:    query_can_fartell_unmet
 * Description: Returns whether the boolean flag is set to allow unmet
 *              people to be sent tells
 */
public nomask int
query_can_fartell_unmet()
{
    return Fartell_unmet;
}

/*
 * Function:    query_can_fartell_wizard
 * Description: A player's ability to send a tell to a wizard will be
 *              defined by this function. It can be masked so that guild
 *              tells can be customized to reach guildmasters, for example.
 *              By default, this contains all the conditions in the targeting
 *              function.
 */
public int
query_can_fartell_wizard(object caster, object wizard)
{
    string wizard_name = wizard->query_real_name();
    
    if (wizard->query_invis() || !wizard->query_prop(LIVE_I_ALWAYSKNOWN))
    {
        hook_fartell_target_unavailable(caster, wizard_name);
        return 0;
    }
    else if (wizard->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M)
    {
        caster->catch_tell("You sense that " 
            + capitalize(wizard_name) + " does not wish to be disturbed.\n");
        return 0;
    }        
    else if (!query_can_fartell_unmet() && !caster->query_met(wizard_name))
    {
        // The caster has not met the target, and the spell does not allow
        // this.
        hook_fartell_target_unmet(caster, wizard_name);
        return 0;
    }
    else if (!is_valid_fartell_target(caster, wizard))
    {
        hook_fartell_target_not_valid(caster, wizard_name);
        return 0;
    }
    
    return 1;
}

/*
 * Function:    set_can_fartell_unmet
 * Description: Call this in your config function to set whether tells
 *              can be sent to those who are unmet.
 */
public void
set_can_fartell_unmet(int bCanTellUnmet)
{
    Fartell_unmet = bCanTellUnmet;
}

/*
 * Function:    config_fartell_spell
 * Description: Config function for fartell spells. Redefine this in your
 *              own fartell spells to override the defaults.
 */
public void
config_fartell_spell()
{
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_stationary(1);
    set_spell_target(target_fartell_spell);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("fartell");
    set_spell_desc("Send someone a tell");

    set_spell_mana(15); // special exception for tell spells. Normal spells
                        // are normally 30 mana.
    set_spell_task(TASK_SIMPLE);
    set_spell_time(2);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(0);
    set_spell_ingredients(query_fartell_ingredients);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    
    set_can_fartell_unmet(1);
        
    // Call the specific configuration that is to be masked.
    config_fartell_spell();
    
    // Call this after the config_fartell_spell to ensure that
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
    resolve_fartell_spell(caster, targets, resist, result);

    mixed input = targets[0];
    object target = input[0];
    string message_text = input[1];
    
    hook_do_fartell_spell(caster, target, message_text);
    hook_send_gmcp_comms(caster, target, message_text);
}

public nomask mixed * 
target_fartell_spell(object caster, string str)
{
    object target;
    string target_name, message_text;
    
    if (!strlen(str))
    {
        hook_fartell_no_target(caster);
        return ({ });
    }

    if (!sscanf(str, "%s %s", target_name, message_text))
    {
        hook_fartell_no_message(caster);
        return ({ });
    }
    
    target_name = lower_case(target_name);
    target = find_player(target_name);

    if (!objectp(target) || target->query_prop(LIVE_I_NEVERKNOWN))
    {
        hook_fartell_target_unavailable(caster, target_name);
        return ({ });
    }
    else if (target == caster)
    {
        hook_fartell_self(caster);
        return ({ });
    }    
    else if (target->query_wiz_level())
    {
        // Wizards are handled differently than regular players.
        // The messages will be inside of query_can_fartell_wizard, so only
        // need to return the target array.
        if (query_can_fartell_wizard(caster, target))
        {
            return ({ ({ target, message_text }) });
        }
        return ({ });
    }
    else if (!query_can_fartell_unmet() && !caster->query_met(target_name))
    {
        // The caster has not met the target, and the spell does not allow
        // this.
        hook_fartell_target_unmet(caster, target_name);
        return ({ });
    }
    else if (!is_valid_fartell_target(caster, target))
    {
        hook_fartell_target_not_valid(caster, target_name);
        return ({ });
    }
    
    return ({ ({ target, message_text }) });     
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_fartell_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_fartell_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    is_valid_fartell_target
 * Description: Called from target_fartell_spell, a customized spell should
 *              mask this and add any restrictions (such as guild members)
 *              on top of the base restrictions in targetting.
 * Returns:     0/1 - not valid/valid target
 */
public int
is_valid_fartell_target(object caster, object target)
{
    return 1;
}

/*
 * Function:    hook_fartell_no_target
 * Description: Override to customize the message for when the caster doesn't
 *              specify a target.
 */
public void
hook_fartell_no_target(object caster)
{
    caster->catch_tell("Who do you wish to send to?\n");
}

/*
 * Function:    hook_fartell_self
 * Description: Override to customize the message for when the caster tries
 *              to send to him/herself.
 */
public void
hook_fartell_self(object caster)
{
    caster->catch_tell("Pretty silly to send something to yourself, no?\n");
}

/*
 * Function:    hook_fartell_no_message
 * Description: Override to customize the message for when the caster doesn't
 *              specify a text to send.
 */
public void
hook_fartell_no_message(object caster)
{
    caster->catch_tell("What do you want to send?\n");
}

/*
 * Function:    hook_fartell_target_unavailable
 * Description: Override to customize the message for when the target cannot
 *              be reached. This includes invis wizards
 */
public void
hook_fartell_target_unavailable(object caster, string target)
{
    caster->catch_tell("You do not sense " + capitalize(LANG_POSS(target)) 
        + " presence in the realms.\n");    
}

/*
 * Function:    hook_fartell_target_not_valid
 * Description: Override to customize the message for when the target cannot
 *              be reached because is_valid_fartell_target returns false
 */
public void
hook_fartell_target_not_valid(object caster, string target)
{
    caster->catch_tell("You cannot seem to reach " + capitalize(target)
        + ".\n");
}

/*
 * Function:    hook_fartell_target_unmet
 * Description: Override to customize the message for when the caster hasn't
 *              met the target, and the spell doesn't allow it.
 */
public void
hook_fartell_target_unmet(object caster, string target)
{
    caster->catch_tell("You can't send a tell to someone you haven't met.\n");
}

/*
 * Function:    hook_send_gmcp_comms
 * Description: Override this hook to customize the message that gets sent
 *              over GMCP.
 */
public void
hook_send_gmcp_comms(object caster, object target, string message_text)
{
    string spell_name = query_spell_name();
    string caster_name = target->query_met(caster) ? capitalize(caster->query_real_name()) : "someone";
    string target_name = capitalize(target->query_real_name());
    caster->gmcp_comms(spell_name, 0, "You send a message to " + target_name + ": " + message_text);
    target->gmcp_comms("fartell", caster_name, "You receive a message from " + caster_name + ": " + message_text);
}

/*
 * Function:    hook_do_fartell_spell
 * Description: Override this to customize the tell spell descriptions. Make sure
 *              to also override hook_send_gmcp_comms if you want to customize
 *              how it looks to GMCP clients.
 */
public void
hook_do_fartell_spell(object caster, object target, string message_text)
{
    target->catch_msg("You receive a message from " + QNAME(caster) + ": "
        + message_text + ".\n");
    caster->catch_msg("You send a message to " + capitalize(target->query_name()) 
        + ": " + message_text + ".\n");
}

/*
 * Function:    query_fartell_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_fartell_ingredients(object caster)
{
    return ({ "silver coin" });
}
