/*
 * cadu_s6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>

void
create_room()
{
    set_short("On a small cliff");
    set_long("You are standing on a small cliff near Cadu. Below you, "+
             "to the south, the waves of the sea hit the bare rock. It "+
             "looks like it is possible to climb down there.\n");

    add_exit("cadu_s4", "east");

    OUTSIDE;
    BEACH;
}

int
climb(string s)
{
    NF("Climb where?\n");
    if (s != "down") return 0;

    NF("You are not skilled enough in climbing and decide against " +
       "climbing down.\n");

    if (TP->query_skill(SS_CLIMB) < 10)
	return 0;
    
    TP->move_living("down", NYREESEDIR + "cadu_water2");
    return 1;
}

void
init()
{
    ::init();
    add_action(climb, "climb");
}
