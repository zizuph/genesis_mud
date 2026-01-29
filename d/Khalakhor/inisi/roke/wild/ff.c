/*
 * ff.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated to an abandoned camp with the Golbar camp moved to a new position, Treacher 08/2021
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include "forest.h"

void
create_room()
{
    set_short("Forest");
    set_long("You are standing in the middle of a big forest. You feel " +
             "a little lost, as you look at the big trees around you. " +
             "An old, partly collapsed barricade stands just to the east. " +
             "Behind the barricade you see remains of something that resemblence " +
             "a small camp.\n");

    add_item(({"barricade", "structure"}),
             "The barricade looks abandoned and parts of the structure has collapsed. " +
             "At some point in time it was probably well maintained, and was built "+
             "to prevent anyone from going east.\n");
    add_item(({"remains", "camp", "small camp"}),
             "It looks like remains of a small camp site.\n");

    TREES;
    TREE1;

    add_exit("fd", "east");
    add_exit("fe", "southwest");
}
