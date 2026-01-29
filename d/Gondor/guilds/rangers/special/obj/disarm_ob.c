/*
 * Disarm effect
 * 
 * This is the disable attack effect . It uses the standard disarm attack effect
 * object as a base and merely adds customized messages.
 *
 * Created by Zizuph, Dec 2021
 */
 
#pragma strict_types

#include "/d/Genesis/specials/local.h"    
inherit DISABLE_ATTACK_OBJ_BASE;

#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define DISARM_SUBLOC  "_ranger_disarm_subloc"

/*
 * Function     : create_disable_attack_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_disable_attack_effect()
{    
    set_name("_ranger_disarm_obj");
    add_name( ({"ranger_disarm_obj" }) );
    set_short("hidden ranger disarm object");    
    set_long("A ranger disarm object. One should not be able to see it "
           + "in their inventory.\n");
           
}

public object find_other_ranger_disarm(object* effects)
{
    foreach(object effect : effects)
    {
        if (effect->is_ranger_disarm() &&
            effect != this_object())
        {
            return effect;
        }
    }
    return 0;
}

public int is_ranger_disarm()
{
    return 1;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != DISARM_SUBLOC)
    {
        return "";
    }
    //query_disable_attack_attack_ids()
    int* disabled_ids = ({});
 
    foreach (object effect : carrier->query_disable_attack_effects())
    {
        if (!effect->is_ranger_disarm())
            continue;
        foreach (int id : effect->query_disable_attack_attack_ids())
        {
            if (member_array(id, disabled_ids) < 0)
                disabled_ids += ({ id });
        }
    }
    string* attack_locations = ({});
    foreach (int id : disabled_ids)
    {
        string desc = for_obj->check_call(
            carrier->query_combat_object()->cb_attack_desc(id));
        if (!strlen(desc))
        {
            continue;
        }
        if (member_array(desc, attack_locations) < 0)
        {
            attack_locations += ({ desc });
        }
    }

    if (for_obj == carrier)
    {
        str = "Your grip on your " + COMPOSITE_WORDS(attack_locations)
        + " is tenuous.\n";
    }
    else
    {
        str = capitalize(carrier->query_pronoun()) + " is holding " +
            carrier->query_possessive() + " " + 
            COMPOSITE_WORDS(attack_locations) + " tenuously.\n";
    }

    return str;

}


/*
 * Function     : hook_attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked because the player is stunned
 * Arguments    : player    - player who is trying to attack
 *                attack_id - attack ID that was blocked
 *                weapon    - weapon in that attack ID, if known.
 * Returns      : nothing
 */
public void
hook_attack_blocked(object player, int attack_id, object weapon)
{
    object enemy, attacker, defender;
    
    enemy = player->query_attack();
    attacker = query_effect_caster();
    defender = query_effect_target();
    if (objectp(enemy))
    {
        // There's a person that is being fought. We display messages
        // about the stun.
        player->catch_msg("You attempt to attack " + QTNAME(enemy)
            + ", but your hand hurts too much to swing.\n");
        enemy->catch_msg(QCTNAME(player) + " makes an aggressive move "
            + "towards you, but is struggling with " +
            player->query_possessive() + " " + weapon->short() + ".\n");
        tell_room(environment(player), QCTNAME(player) + " tries to "
            + "attack " + QTNAME(enemy) + ", but seems to be "
            + "having trouble with " +
            player->query_possessive() + " " + weapon->short()+
            ".\n" , enemy, ({ player, enemy }));                     
    }
}

public void
hook_disable_attack_ended(object player)
{
    if (player->query_hp() > 0)
    {
        player->catch_tell("Your hand no longer hurts from the blow.\n");
   
        tell_room(environment(player), QCTNAME(player) + 
           " looks more confident about " + 
            player->query_possessive() + " attack.\n", player);

        // disarmed may be from a non-ranger ability.
        object other_disarm = find_other_ranger_disarm(
            player->query_disable_attack_effects());
        if (other_disarm)
        {
            player->remove_subloc(DISARM_SUBLOC);
            player->add_subloc(DISARM_SUBLOC, other_disarm);
        }
        else
        {
            player->remove_subloc(DISARM_SUBLOC);
        }
    }
}

public void
hook_disable_attack_failed(object actor, object target)
{    
  actor->catch_msg(QCTNAME(target) + " appears too focused on your " +
     "attack for you to disarm.\n");
}


public void
hook_disable_attack_begin(object actor, object target)
{    
    target->catch_msg(QCTNAME(actor) + " delivers " +
        "a painful blow to your hand!\n");

    actor->catch_msg("You skillfully deliver a painful blow to " +
        target->query_the_possessive_name(actor) + " hand!\n");
    tell_room(environment(actor), QCTNAME(actor) + " delivers a " +
        "painful blow to " + QPNAME(target) + " hand!\n",
        ({ actor, target }) );

        target->add_subloc(DISARM_SUBLOC, this_object());

    if (!find_other_ranger_disarm(
        target->query_disable_attack_effects()))
    {
        target->add_subloc(DISARM_SUBLOC, this_object());
    }
}
