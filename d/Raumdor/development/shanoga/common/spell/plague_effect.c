/*
 * plague_effect.c
 *
 * This object INHERITS the standard poison effect. It will harm people who are
 * hit by the lich's plague swarm spell.
 *
 * Used By: /d/Raumdor/common/npc/lich.c
 *
 * Written by Shanoga under Liege Malus. Updated 2018.03.21
 */

#pragma save_binary
#pragma strict_types

inherit "/std/poison_effect";

#include <files.h>
#include <log.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "defs.h"

#define PLAGUE_MSG ({ \
    "The swarm painfully burrows into your flesh.", \
    "You are in agony as the swarm scrapes against your bones.", \
})


/*
 * Function name: create_poison_effect
 * Description  : The normal create for the poison_effect. Redefine this
 *                function if you want to create your own poison.
 */
public void
create_poison_effect()
{
    set_short("necropathy");
    set_name("necropathy");
    set_long("This is a damage over time inflicted by the plague swarm " +
      "spell of a lich from Raumdor.");
    set_interval(2);
    set_time(10);
    set_damage(({ POISON_HP, 200 }));
    set_strength(1000);
    set_silent(2);
    set_no_cleanse();
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

/*
 * Function name: make_pain
 * Description  : This function prints the pain messages to the player as
 *                called each time the poisonee takes damage.
 */
public void
make_pain()
{
    string plague_message = one_of_list(PLAGUE_MSG);
    
    E(TO)->catch_msg(plague_message + "\n");
}

/*
 * Function name: start_poison
 * Description  : This function simply starts the poison working.  Until the
 *                poison is activated, it is a simple object. Once activated,
 *                the poison will disappear after 'time' seconds.
 * Arguments    : object poisoner - the living that is responsible for the
 *                    poisoning of this player. This could be an NPC or real
 *                    player, if any.
 */
public varargs void
start_poison(object poisoner)
{
    set_alarm(2.0, 2.0, make_pain);
    ::start_poison(poisoner);
}



/*
 * Function name: kill_player
 * Description  : The player has died, so we kill him! 8-)
 */
public void
kill_player()
{
    if (a_time)
    {
        remove_alarm(a_time);
    }
    a_time = 0;

    tell_object(poisonee, "You have died.\n");
    set_alarm(0.0, 0.0, remove_object);
    string killer = query_responsible_object(); //MASTER_OB
    if (killer == "/d/Raumdor/development/shanoga/common/npc/lich")
    {
        previous_object()->notify_you_killed_me(poisonee);
    }
    poisonee->do_die(this_object());
    
}