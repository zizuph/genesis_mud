/*
 * Earth Cleric Evade Spell Object (Skiamorfi)
 *
 * Based on the evade spell effect, this provides Earth Clerics
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

inherit "/d/Genesis/specials/std/spells/obj/evade_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_s_evade_object");
    set_short("skiamorfi evade object");    
    set_long("This is the skiarmofi evade object. It provides "
        + "the caster with an evade effect.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the skiamorfi spell.\n");
    set_spell_effect_desc("skiamorfi evade");    
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
    
    string caster_message = "You sense that Lady Gu sends her blessed winds "
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
