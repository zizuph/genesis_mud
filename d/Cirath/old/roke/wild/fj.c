/*
 * fj.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
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
    set_long("This is a small forest path, leading east and west from " +
             "here. Around you the trees grow thick, but to the west " +
             "the forest looks a little thinner and you also think that " +
             "the path widens a little in that direction.\n");

    TREES;
    TREE1;

    add_exit("fk", "east");
    add_exit("fi", "west");
}
