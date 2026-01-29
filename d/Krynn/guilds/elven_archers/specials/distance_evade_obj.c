/*
 */

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

#include "/d/Genesis/specials/defs.h"

inherit EVADE_OBJ_BASE;

#include "../guild.h"
#include "missile_functions.c"

/*
 * Function name:   create_effect
 * Description:     The create function called for objects that inherit this.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_effect()
{
    set_name("_archer_evade_object_");
    add_name( ({"archer_evade_object" }) );
    set_short("hidden archer evade object");
    set_long("The object that grants evade to archers.\n");

    setuid();
    seteuid(getuid());

    set_evade_stats(({ SKILL_WEIGHT, 60, TS_DEX, SKILL_WEIGHT, 25, TS_WIS, 
                  SKILL_WEIGHT, 15, TS_INT }));
    set_evade_skills(({ SS_GUILD_EVASION }));

    set_evade_combat_aid(32);
} /* create_effect */

/*
 * Function name:   is_distance_evade_object
 * Description:     Allows filters to identify this particular object easily
 * Arguments:       None
 * Returns:         (status) 1 - always true
 */
public status
is_distance_evade_object()
{
    return 1;
} /* is_distance_evade_object */

/*
 * Function name:   attack_blocked
 * Description:     Function to display messages that the attack was blocked.
 * Arguments:       (object) player    - player who is being attacked
 *                  (object) attacker  - the person doing the attacking
 *                  (int)    attack_id - attack id location
 * Returns:          Nothing
 */
public void
attack_blocked(object player, object attacker, int attack_id)
{
    object  steed;
    int     rnd_msg;
    string  avoiding,
           *player_msg,
           *target_msg,
           *others_msg;

    avoiding = one_of_list(({
        "evading", "dodging", "avoiding"
    }));
    //    feint, sidestep, turn aside, shift, elude, obviate, avoid, 
    
    if (objectp(steed = player->query_steed()))
    {
        player_msg = ({
            "You maneuver " + QTNAME(steed) + " to distance yourself from "
            + attacker->query_the_name(player) + ", " + avoiding
            + " an attack in the process.\n",
        });
        target_msg = ({
            player->query_The_name(attacker) + " maneuver " + QTNAME(steed)
            + ", distancing " + player->query_objective() + "self from you, "
            + "just narrowly " + avoiding + " your attack in the process.\n",
        });
        others_msg = ({
            QCTNAME(player) + " maneuver " + QTNAME(steed) + " to distance " 
            + player->query_objective() + "self from " + QTNAME(attacker) + ", "
            + "narrowly " + avoiding + " " + QTNAME(attacker) + "'s attack.\n",
        });
    }
    else
    {
        player_msg = ({
            "You leap back to distance yourself from "
            + attacker->query_the_name(player) + ", " + avoiding
            + " an attack in the process.\n",
            "You sidestep in an attempt to distance yourself from "
            + attacker->query_the_name(player) + " successfully " + avoiding
            + " an incoming attack.\n",
            "You retreat a few steps to increase the distance between yourself "
            + "and " + attacker->query_the_name(player) + ".\n"
        });
    
        target_msg = ({
            player->query_The_name(attacker) + " suddenly leaps back, "
            + "distancing " + player->query_objective() + "self from you, just "
            + "narrowly " + avoiding + " your attack in the process.\n",
            player->query_The_name(attacker) + " sidesteps your attack and "
            + "attempt to increase the distance between "
            + player->query_objective() + "self and you.\n",
            player->query_The_name(attacker) + " retreats a few steps in order "
            + "to distance " + player->query_objective() + "self from you.\n"
        });
    
        others_msg = ({
            QCTNAME(player) + " leaps back in an attempt to distance " 
            + player->query_objective() + "self from " + QTNAME(attacker) + ", "
            + "narrowly " + avoiding + " " + QTNAME(attacker) + "'s attack.\n",
            QCTNAME(player) + " sidesteps " + QTNAME(attacker) + "'s attack "
            + "and increases the distance between them.\n",
            QCTNAME(player) + " retreats a few steps away from "
            + QTNAME(attacker) + " increasing the distance between them.\n"
        });
    }
    rnd_msg = random(sizeof(player_msg));
    
    player->catch_msg(player_msg[rnd_msg]
    + (attack_id == -1 ? "Your maneuvering had a monumental effect on "
    + attacker->query_the_name(player) + "'s offensive strategy.\n" : ""));
    
    attacker->catch_msg(target_msg[rnd_msg]
    + (attack_id == -1 ? player->query_The_name(attacker) + "s maneuvering had "
    + "a monumental effect on your offensive strategy.\n" : ""));
    
    player->tell_watcher(others_msg[rnd_msg], ({ attacker }));
    
} /* attack_blocked */

/*
 * Function name:   query_evade_valid
 * Description:     Validation function to see whether this evade object is
 *                  valid in the current situation
 * Arguments:       (object) player     - player who is being attacked
 *                  (object) attacker   - the person doing the attacking
 *                  (int)    attack_id  - attack id location
 * Returns:         (int)    0/1        - invalid/valid
 */
public int
query_evade_valid(object player, object attacker, int attack_id)
{
    /* We don't want to evade if we have recently sniped. */
    return !SNIPE->query_ability_active(player);
} /* query_evade_valid */