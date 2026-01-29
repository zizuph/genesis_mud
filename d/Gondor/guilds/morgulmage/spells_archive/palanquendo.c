/*
 * Tell Spell for the Morgul Mages
 *
 * Created by Eowul, September 2009
 */

#pragma strict_types

#include "../morgulmage.h"
#include <options.h>
#include <macros.h>
#include <flags.h>
#include <tasks.h>
#include <language.h>

inherit "/d/Genesis/specials/std/spells/fartell";

#define _NO_PREP_TIME_ADJUSTMENT

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

/*
 * Function:    config_fartell_spell
 * Description: Config function for fartell spells. Redefine this in your
 *              own fartell spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public varargs int
config_fartell_spell()
{
    set_spell_name("palanquendo");
    set_spell_desc("Send a message to a distant target");

    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_resist(0);

    set_can_fartell_unmet(1);

    set_spell_element(SS_ELEMENT_AIR, 1);
    set_spell_form(SS_FORM_CONJURATION, 1);

    set_spell_task(TASK_EASY);

    set_spell_time_factor(&adjust_time_by_rank(0.5));

    set_morgul_rank(0);
    return 0;
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
    int special_wizard = IS_MEMBER(wizard);

    if (!special_wizard || wizard->query_invis()
        || !caster->query_met(wizard_name))
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
    else if (!is_valid_fartell_target(caster, wizard))
    {
        hook_fartell_target_not_valid(caster, wizard_name);
        return 0;
    }

    return 1;
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
    if(target->query_prop("_player_s_ld_in_room"))
        return 0;

    return 1;
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
    caster->catch_tell("Your message couldn't reach its destination and "
        + "was lost in the void.\n");
}

private string break_message_when_needed(object target, string message)
{
    int width = target->query_option(OPT_SCREEN_WIDTH);
    if (width == -1) return "\t" + message;
    return break_string(message, width - 10, "\t");
}

/*
 * Function:    hook_send_gmcp_comms
 * Description: Override this hook to customize the message that gets sent
 *              over GMCP.
 */
public void
hook_send_gmcp_comms(object caster, object target, string message_text)
{
    // We don't use this function but instead send the GMCP calls in the
    // hook_do_fartell_spell function, since we have use various different
    // messages
}

/*
 * Function:    hook_do_fartell_spell
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_do_fartell_spell(object caster, object target, string message_text)
{
    string cast_str = one_of_list(({
        "With the power the Dark Lord has bestowed upon you, you tell ",
        "Using the powers the Black Master has bestowed upon you, you tell ",
        "With a touch of the Dark Lord's powers, you tell ",
        "Using a touch of the power the Black Master has granted you, you tell ",
        }));

    can_see_caster(caster)->catch_msg("Employing Dark Sorcery, "
        + QTNAME(caster) + " casts a spell.\n");
    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_msg(cast_str + target->query_met_name() + ":\n"
            + break_message_when_needed(caster, message_text) + "\n");
    }
    else
    {
        caster->catch_msg("With the power the Dark Lord has bestowed "
            + "upon you, you send a message to "
            + target->query_met_name() + ".\n" );
    }
    caster->gmcp_comms("palanquendo", 0, cast_str + target->query_met_name() +
        ": " + message_text);

    if (target->query_npc())
    {
        target->hook_received_palanquendo(caster, message_text);
    }

    object ring = present(MORGUL_MORGUL_RING, caster);
    if (objectp(ring))
    {
        if (target->query_met(caster->query_real_name()))
        {
            string effect_message = "An image of " + LANG_ADDART(ring->short())
                + " appears in your mind; and from it the fell voice of "
                + caster->query_name() + " says: ";
            target->catch_msg(effect_message + "\n"
                + break_message_when_needed(target, message_text) + "\n");
            target->gmcp_comms("fartell", caster->query_name(), effect_message
                + message_text);
        }
	else
	{
            string effect_message = "An image of " + LANG_ADDART(ring->short())
                + " appears in your mind; and from it a fell voice says: ";
            target->catch_msg(effect_message + "\n"
                + break_message_when_needed(target, message_text) + "\n");
            target->gmcp_comms("fartell", "Someone", effect_message
                + message_text);
        }
    }
    else
    {
        string effect_message = "With the help of Dark Sorcery, "
            + caster->query_art_name(target) + " tells you: ";
        target->catch_msg(effect_message + "\n"
            + break_message_when_needed(target, message_text) + "\n");
        target->gmcp_comms("fartell", caster->query_Art_name(target),
            effect_message + message_text);
    }

    MORGUL_MASTER->increase_activity(caster, ACTIVITY_SMALL_SPELL);
}

/*
 * Function:    query_fartell_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_fartell_ingredients(object caster)
{
    if(caster->query_attack())
    {
        return ({ "silver coin" });
    } else {
        return ({ "copper coin" });
    }
}

/*
 * Function:    resolve_fartell_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_fartell_spell(object caster, mixed * targets, int * resist, int result)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_SMALL_SPELL);
}
