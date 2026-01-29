/*
 * cas_c4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object guard;

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You have stopped in a corner. The black walls seem to be closing " +
             "in. There is something with this place that makes you shiver. An " +
             "air of magic rests all around you. You see two large doors here, " +
             "one is to the west and one is south of you. You could also enter " +
             "a tower to the northeast.\n");

    INSIDE;
    add_exit("cas_t32", "northeast");
    add_exit("cas_c3", "west");
    add_exit("cas_c8", "south");
}
