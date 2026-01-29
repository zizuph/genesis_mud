/*
 *  /d/Gondor/guilds/rangers/ithilien/landing.c
 *
 * Modification log:
 * 20-Jul-2001,Alto: tidy up, change inheritance for new
 *                   rangers.
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "exit.c"

#define MOVING_THROUGH_VANTAGE       "_moving_through_vantage"

/* Prototypes */
public string      long_func();
public int         exit_room();
public int         grasp_cord(object actor);


public void
create_gondor()
{
    set_short("a wide flat rock above the waterfall");
    set_long(&long_func());
    add_item(({"cord", "long cord"}), "Someone has mounted a long cord to "
        + "the edge of the rock. As you carefully examine the cord, you see "
        + "that it is very strong, but also stretches! It may be possible "
        + "to grasp it and leap off the edge of the rock. Hopefully you are "
        + "not too heavy, because if the cord breaks under your weight, it is "
        + "a long way down.\n");
    add_item("rock", "You are standing on a wide flat rock above the "
        + "waterfall, which is wet and slippery from the mist of the "
        + "falls.\n");
    add_item(({"waterfall", "fall", "torrent", "stream"}), "Eastwards is the "
        + "waterfall, splashing over many terraces, and then, pouring down "
        + "a steep race, it fills a smooth-hewn channel with a dark force "
        + "of water flecked with foam, and curling and rushing almost at "
        + "your feet it plunges sheer over the edge that yawns to the "
        + "west.\n");
    add_item("vale", "It is a great vale, with a silvery spine running from "
        + "north to south - the River Anduin.\n");
    add_item(({"field", "fields"}), "The fields are green, with a silvery "
        + "spine  running from north to south - the River Anduin.\n");
    add_item(({"water", "river","anduin"}), "The river you can see in the "
        + "west is the mighty Anduin, on its way to the Sea. The torrent "
        + "at your feet seems to be one of its tributes.\n");
    add_item(({"terrace", "terraces"}), "The terraces consist of large, "
        + "flat rocks, smoothed by thousands of years of water flowing over "
        + "their surface.\n");
    add_item("cleft", "The cleft is a V-shaped fissure, filled with "
        + "foaming water.\n");
    add_item(({"pool"}), "You could probably see it better if you moved to "
        + "the west a little.\n");
    add_item(({"edge"}), "You lean over the edge of the rock and get a little "
        + "dizzy from the height.\n");
    add_exit(RANGERS_ITH_DIR + "landing2", "west", &check_ranger());

    add_cmd_item(({"cord", "the cord", "long cord", "the long cord"}),
        "grasp", &exit_room());

    add_prop(ROOM_M_NO_SCRY, 1);
    reset_room();

}


public string
long_func()
{
    string text;
    text= "You are on a wide flat rock without rail or parapet. Just to "
        + "the east, the torrent stream falls, splashing over many "
        + "terraces and flowing west to fill a smooth cleft with foaming "
        + "water. The rock is wet from the thin mist rising from the cleft. "
        + "In the distance to the west stretches an immense vale";

    if (tod() == "night")
        text += ", filled with a silvery mist lit by the moon.\n";
    else
        text += ", its green fields lit by the sun. Its epic beauty "
            + "astounds you - Gondor, Oh Gondor!\n";

    return (text + "There is a long cord mounted at the edge of the rock.\n"); 
}

public int
finish_moving(object actor)
{
    actor->remove_prop(MOVING_THROUGH_VANTAGE);
    return 1;
}

public int
grasp_cord(object actor)
{
    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You grasp the long cord and "
        + "take a running leap over the edge of the rock.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("Whee! You fall rapidly down of "
        + "the edge the cliff!\n\n"));
    set_alarm(3.0, 0.0, &actor->catch_tell("As you near the bottom, the "
        + "cord reaches its greatest length. Just as it begins to retract, "
        + "you let go, somersault through several tight spins and dive "
        + "into the pool!\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " grasps the long cord "
        + "and takes a running leap over the edge of the rock!\n", 
        ({ actor }));

    set_alarm(3.0, 0.0, &finish_moving(actor));

    return 1;
}


public int
exit_room()
{
    object tp = this_player();

    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    grasp_cord(tp);
    set_alarm(4.0, 0.0, &move_ranger(tp));        
    return 1;
}


public int
move_ranger(object who)
{
    say(QCTNAME(who) + " somersaults through several tight spins and dives "
        + "into the pool below!\n");
    tell_room(RANGERS_ITH_DIR + "pool", QCTNAME(who) + " suddenly drops "
        + "in from high above, does a few somersaults and dives into the "
        + "pool!\n", ({who}));

    who->move_living("M", RANGERS_ITH_DIR + "pool", 1, 0);
    return 1;
}

