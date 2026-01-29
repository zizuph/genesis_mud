/*
 * deck.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Ported to the new ship system by Tapakah, 10/2008
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../../defs.h"
#include <macros.h>
#include <ss_types.h>
#include "/d/Genesis/ship_new/ships.h"

inherit STDSHIPROOM;

void jump2(object tp);

void
create_room()
{
	::create_shiproom();
    set_short("On the large warship");
    set_name("water");
    set_long("You are standing on the deck of a huge warship sailing " +
             "between Nyreese and Sparkle. Some sailors are working high up " +
             "in the masts, and beside you stands the admiral, giving " +
             "orders to the crew. Around you are various items: long " +
             "ropes, buckets of water, and not to forget, the impressive " +
             "catapults of the ship. There is also a staircase leading down " +
             "towards the admiral's cabin.\n");

    add_item(({"mast", "masts"}),
             "There are three great masts " +
             "supporting the enormous sails, and you can see people high up " +
             "climbing about.\n");
    add_item(({"sail", "sails"}),
             "The sails are made out of thick, incredibly strong canvas, " +
             "but you can't see that from down here really. What you see is " +
             "that the sails are set and when a gust of wind fills one or " +
             "several, you feel a rift going " +
             "through all of the ship and notice the masts swaying slightly " +
             "to the enormous pressure.\n");
    add_item(({"catapult", "catapults"}),
             "The catapults are brand new " +
             "and you realize this is probably the best weaponry that " +
             "money can buy. The craftsmanship is excellent.\n");
    add_exit("cabin", "down");
    add_prop(ROOM_I_NO_DIG, 1);
}

int
jump(string s)
{
    if (!s || s == "") 
    {
        write("Jump where? Overboard?\n");
        return 1;
    }

    if (s != "overboard")
    {
        notify_fail("Jump where? Overboard?\n");
        return 0;
    }

    say(QCTNAME(TP) + " jumps overboard.\n");

    TP->move_living("M", ENV(ship));

    set_alarm(1.0, 0.0, &jump2(TP));

    return 1;
}

void 
jump2(object tp)
{
    if (ENV(tp)->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
    {
        tp->catch_msg("You hit the ground with your head first! It hurts terribly!\n");
        tell_room(TO, QCTNAME(tp) + " hits the ground with " +
                  tp->query_possessive() +
                  " head first. It sounds awful.\n");
        tp->heal_hp(-tp->query_max_hp() / 3);
        if (tp->query_hp() == 0)
            tp->do_die(TO);
        return;
    }
    tp->catch_msg("You jump into the fresh, cold water.\n");

    if (!tp->query_skill(SS_SWIM))
    {
        tp->catch_msg("Unfortunately you never learned to swim. You panic, " +
                      "and are unable to avoid drowning.\n");
        tell_room(TO, QCTNAME(tp) +
                  " seems to be unable to swim and drowns.\n");
        tp->heal_hp(-300784);
        tp->do_die(TO);
        //ROKE_LOG("drowned", capitalize(tp->query_real_name()) +
        //         " (From the ship) " + ctime(time()) + "\n");
    }
}

void
init()
{
    ::init();

  //    add_action("jump", "jump"); NOT in the new version
  
}
