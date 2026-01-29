/*
 * cas_a1.c
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
    set_long("You find yourself standing in a small room inside " +
             "the castle. To the northwest is the entrance of what " +
             "looks like a tower.\n");
    INSIDE;
    add_exit("cas_t11","northwest");
    add_exit("cas_a2", "east");
    add_exit("cas_a5", "south");
}
