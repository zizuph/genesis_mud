/*
 * cas_c3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
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
    set_long("This is the top of the stairs to third level of the castle.\n" +
             "You see that the walls around you are really dark, and you wonder " +
             "how it's possible for the ceiling to emit light. But, mind you, " +
             "this is the castle of a great magician...\n" +
             "You see a flight of stairs leading down and the dark corridor " +
             "leading east.\n");

    INSIDE;
    add_exit("cas_c4", "east");
    add_exit("cas_b3", "down");
}
