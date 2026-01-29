/*
 * cas_b6.c
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
    set_long("This is a hall with beautiful ornaments decorating " +
             "the walls. The hall has large open entrances to " +
             "the east and south.\n");

    add_item(({"ornaments", "wall"}),
             "It makes you imagine the glory of past battles.\n");

    add_exit("cas_b7", "east");
    add_exit("cas_b5", "west");
    add_exit("cas_b10", "south");
    INSIDE;
}
