/*
 * cas_a8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    INSIDE;

    set_short("In the middle of the Castle");
    set_long("You are standing in an intersection in one of the " +
             "corridors of the castle. As you carefully look around " +
             "you notice small openings in the wall far away to the " +
             "north and south.\n");

    add_exit("cas_a4",  "north");
    add_exit("cas_a7",  "west");
    add_exit("cas_a12", "south");
}
