/*
 * cas_b8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This is a cold, narrow corridor.\n" +
             "A thin share of light cuts through the corridor " +
             "coming from a window high up the east wall.\n");

    add_item("window", "It is too high up for you to see anything.\n");

    add_exit("cas_b4", "north");
    add_exit("cas_b12", "south");
    INSIDE;
}
