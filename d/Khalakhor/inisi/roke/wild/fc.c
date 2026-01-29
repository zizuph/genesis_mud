/*
 * fc.c
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
    set_long("You are walking around in the middle of the dark forest. The " +
             "trees around you are very large, and you can hardly see any " +
             "light here. An old, partly collapsed barricade stands just to the south.\n");

    add_item(({"barricade", "structure"}),
             "The barricade looks abandoned and parts of the structure has collapsed. " +
             "At some point in time it was probably well maintained, and was built "+
             "to prevent anyone from continuing south.\n");

    TREES;
    TREE1;

    add_exit("fa", "north");
    add_exit("fd", "south");
    add_exit("fm", "east");
}

