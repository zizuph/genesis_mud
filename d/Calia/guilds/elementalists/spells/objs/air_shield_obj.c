/*
 * Elementalist Air Shield Spell Object (Schirmo)
 *
 * Based on the evade spell effect, the air shield provides Elementalists
 * with an evade ability.
 *
 * Created by Petros, February 2013
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "evade_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_air_shield_object");
    set_short("schirmo air shield object");    
    set_long("This is the schirmo air shield object. It provides "
        + "the caster with an evade effect.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the schirmo elemental shield "+
                            "spell.\n");
}

public int
setup_spell_effect()
{
    set_spell_effect_desc("schirmo air shield");    
    return ::setup_spell_effect();
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (!objectp(target))
    {
        return;
    }
    object caster = query_effect_caster();
    
    string caster_message = "As you complete your prayer to Lady Aeria, "
        + "you sense the winds pick up as she sends her blessed winds "
        + "to keep you out of harm's way. ";
    string target_message = "The air moves invisibly and turns into a moaning "
        + "wind that becomes a chaotic whistle before settling into an "
        + "airy shield that surrounds you.\n";
    string watcher_message = "The air moves invisibly and turns into a moaning "
        + "wind that becomes a chaotic whistle before settling into an "
        + "airy shield that surrounds " + QTNAME(target) + ".\n";
    if (target == query_effect_caster())
    {
        caster->catch_msg(caster_message + target_message);
    }
    else
    {
        caster->catch_msg(caster_message + "\n");
        target->catch_msg(target_message);
    }
    tell_room(environment(target), watcher_message, ({ target, caster }));
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (!objectp(target))
    {
        return;
    }
    target->catch_tell("The chaotic wind surrounding you dissipates, taking "
        + "the airy gift of Lady Aeria with it.\n");
    tell_room(environment(target), "The chaotic wind surrounding "
        + QTNAME(target) + " dissipates.\n", ({ target }));
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the strength of the chaotic wind "
            + "surrounding you begin to ebb.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Mentally drained, you lose control of "
            + "the airy elemental powers sustaining the "
            + "schirmo gift of Lady Aeria.");
    }    
}

/*
 * Function:    query_evade_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_evade_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are surrounded by a chaotic shifting wind.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrounded by "
            + "a chaotic shifting wind.\n";
}

/*
 * Function     : hook_describe_evade_effect
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
hook_describe_evade_effect(object player, object attacker, int attack_id)
{
    player->catch_msg(QCTNAME(attacker) + " misses you with "
        + attacker->query_possessive() + " attack as a sudden burst "
        + "from the chaotic shifting wind surrounding you forces "
        + "the blow aside.\n");
    attacker->catch_msg("You miss " + QTNAME(player) + " with your "
        + "attack as a sudden burst from the chaotic shifting wind "
        + "surrounding " + player->query_objective() + " forces your "
        + "blow aside.\n");
    tell_room(environment(player), QCTNAME(attacker) + " misses "
        + QTNAME(player) + " with " + attacker->query_possessive()
        + " attack as a sudden burst from the chaotic shifting wind "
        + "surrounding " + QTNAME(player) + " forces the attack "
        + "aside.\n", 
            ({ player, attacker }), player);
}
