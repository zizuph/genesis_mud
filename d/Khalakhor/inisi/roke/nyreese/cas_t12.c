/*
 * cas_t12.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

int i;

void reset_room();

void
create_room()
{
    set_short("Northeast tower of the castle");
    set_long("You are in the northeast tower. The walls looks " +
             "as if they will fall down anytime around you, and " +
             "when you walk around on the floor it feels like the " +
             "stones are loose...\nThere is a window in the wall.\n");

    add_item("walls",
             "You are afraid that if you touch them, they will fall.\n");
    add_cmd_item("walls", "touch", "Phew! They seemed to withstand that.\n");

    add_item("floor", "The stones are loose here.\n");
    add_item(({"stone", "stones"}), "One of them looks like it's liftable.\n");
    add_cmd_item("stone", "lift", "@@liftit");

    add_item("window",
             "It is filled with stones, so you can't look through it.\n");
    add_cmd_item(({"window", "through window"}), "look",
                 "It is filled with stones, so you can't look through it.\n");

    add_exit("cas_a4", "southwest");

    reset_room();
    INSIDE;
    DARK;
}

int
liftit()
{
    if (TP->query_stat(0) < 14)
    {
        write("You are not strong enough!\n");
        say(QCTNAME(TP) + " tries to lift a stone but fails.\n");
        return 1;
    }

    if (i || QDONE(ROKEGROUP, SCROLLQUEST))
    {
        say(QCTNAME(TP) + " lifts a stone.\n");
        write("You lift the stone but find nothing.\n");
        return 1;
    }
    i = 1;
    say(QCTNAME(TP) + " lifts a stone and finds something.\n");
    write("You lift the stone and under it you find a magic scroll!\n");

    clone_object(ROKEDIR + "obj/cas_scroll")->move(TP);

    return 1;
}

void
reset_room()
{
    i = 0;
    if (MAL("guard"))
        return;

    clone_object(ROKEDIR + "npc/towerg1")->move(TO);
    tell_room(TO, "The tower guard arrives.\n");
}
