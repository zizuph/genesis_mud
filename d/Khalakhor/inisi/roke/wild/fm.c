/*
 * fm.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "forest.h"

void
create_room()
{
    set_short("Edge of the forest");
    set_long("You are on a small road on the edge of the forest. " +
             "The road is muddy and there are lots of tracks here. " +
             "Far to the east you can see large mountains and to the west " +
             "the forest grows deeper.\n");
    add_item("tracks", "There are many tracks here, but you cannot make" +
             " out who or what made them.\n");

    TREES;
    TREE1;

    add_exit("fc", "west");
    add_exit("fl", "southeast");
}
