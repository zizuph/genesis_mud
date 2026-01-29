/*
 * File: basic_special.c
 * Description: A (relatively) quick way to do a basic special attack.
 * Authors: Rhyn
 * Created: Jan 19 2001
*/

#pragma strict_types

inherit "/d/Earthsea/lib/commands";

#include "basic_special.h"
#include <filter_funs.h>
#include <wa_types.h>

private string watcher_message, watcher_message_end;
private string target_message;
private string player_message;
private mapping result_messages; // ([ proc_hurt : message ])

/*
 * Function name: set_player_message
 * Description: Sets the message to be displayed to the caster with actor()
 * Arguments: string str - the message
 * Returns:
*/
public void
set_player_message(string str)
{
    player_message = str;
}

/*
 * Function name: set_target_message
 * Description: Sets the message to be displayed to the target with target()
 * Arguments: string str - the message
 * Returns:
*/
public void
set_target_message(string str)
{
    target_message = str;
}

/*
 * Function name: set_watcher_message
 * Description: Sets the message to be displayed to people in the room.
 * Arguments: string str - first part of all2act, str2 - last part
 * Returns:
*/
public varargs void
set_watcher_message(string str, string str2 = ".")
{
    watcher_message = str;
    watcher_message_end = str2;
}

/*
 * Function name: set_result_messages
 * Description: Sets the messages to be displayed for various proc_hurt
 *              ranges, basically the % success.
 * Arguments: mapping messages - a mapping of integers and strings like:
 *            ([ 10, "You don't feel much.\n", 50, "You feel alot.\n" ])
 *            The integer is proc_hurt.
 * Returns:
*/
public void
set_result_messages(mapping messages)
{
    result_messages = secure_var(messages);
}

public int
gt(mixed a, mixed b)
{
    if(a < b)
    {
        return -1;
    }

    if(a > b)
    {
        return 1;
    }

    return 0;
}

/*
 * Function name: basic_special
 * Description: Performs a basic special attack on a list of targets and
 *              displays a message to everyone, using the pre-set messages.
 * Arguments:
 *              object attacker - the person doing the special
 *              int pen - the weapon pen for hit_me
 *              int dt - the damage type
 *              int all_or_enemies - if -1, hits all in the room, 1
 *                  hits only people the attacker is fighting, 0 hits
 *                  just attacker's target
 *              function check_do_damage - a function that takes an object
 *                  and returns 1 if it should be hit, else 0. If
 *                  all_or_enemies is greater than 0, this will only be used
 *                  on objects the attacker is already fighting.
 * Returns:
*/
public void
basic_special(
    object attacker,
    int pen = 40,
    int dt = MAGIC_DT,
    int all_or_enemies = 0,
    function check_do_damage = living
)
{
    object *targets;
    int proc_hurt, i, j, last = 0;
    mixed *message_levels = 0;
    mapping message = ([ ]);

    if(all_or_enemies == 1)
    {
        targets = attacker->query_enemy(-1);
    } else if(all_or_enemies == -1) {
        targets = FILTER_LIVE(all_inventory(environment(attacker)));
    } else {
        targets = ({ attacker->query_attack() });
    }

    if(!sizeof(targets))
        return;

    targets = filter(targets, check_do_damage);

    targets = filter(targets, operator(!) @ &->query_not_attack_me(
        this_object(), -1));

    if(!sizeof(targets))
        return;

    if(mappingp(result_messages) && m_sizeof(result_messages))
    {
        message_levels = sort_array(m_indices(result_messages),
            gt);
    }

    for(i=0; i<sizeof(targets); i++)
    {
        proc_hurt = targets[i]->hit_me(
            pen, dt, attacker, -1
        )[0];

        if(message_levels == 0)
            continue;

        if(message_levels[sizeof(message_levels)-1] < proc_hurt)
        {
            message[i] = result_messages[
                message_levels[sizeof(message_levels)-1]
            ];
        }

        while(!stringp(message[i]) && j < sizeof(message_levels))
        {
            if(last <= message_levels[j])
            {
                message[i] = message_levels[j];
            }

            last = message_levels[j];
            j++;
        }

        if(intp(message[i]))
        {
            message[i] = result_messages[message_levels[i]];
        } else if(!stringp(message[i]) || !strlen(message[i])) {
            message[i] = result_messages[message_levels[0]];
        }
    }

    set_this_player(attacker);

    if(player_message)
        actor(player_message, targets);

    if(target_message)
        target(target_message, targets);

    all2act(watcher_message, targets, watcher_message_end);

    if(!m_sizeof(message))
        return;

    for(i=0; i<sizeof(targets); i++)
    {
        targets[i]->catch_msg(message[i] + "\n");
    }
}
