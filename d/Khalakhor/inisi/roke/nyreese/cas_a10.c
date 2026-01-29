/*
 * cas_a10.c
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
    set_long("This is just another ordinary room forming one " +
             "of the long corridors in the castle. However, if " +
             "you look carefully, you can see a faint blue glow " +
             "to the east.\n");

    INSIDE;
    add_exit("cas_a11", "east");
    add_exit("cas_a9",  "west");
}
