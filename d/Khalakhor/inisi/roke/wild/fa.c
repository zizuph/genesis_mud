/*
 * fa.c
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
    set_short("Forest");
    set_long("You are on a small track on the northern edge of the forest. " +
             "There's a lot of high grass stretching north towards the " +
             "mountains far away. South you see the thick and dark forest. " +
             "You feel very peaceful here. The path continues west and " +
             "south. There is also a small opening between the trees " +
             "northeast of here.\n");

    TREES;
    TREE1;

    add_exit("f9", "west");
    add_exit("fc", "south");
    add_exit("r1", "northeast");
}
