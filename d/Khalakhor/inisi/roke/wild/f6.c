/*
 * f6.c
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
    set_short("Sunny meadow");
    set_long("You are standing in the middle of a sunny meadow between " +
             "some of the trees in the forest. A nice looking lawn is " +
             "below you. There is also a track with several fresh foot" +
             "prints here. It stretches from northeast to the southwest. " +
             "Strangely enough there is no track to the west, although " +
             "the woods there look much nicer than to the east.\n");

    TREES;
    TREE2;
    GRASS;
    add_item(({"footprints", "prints", "print"}),
             ("These prints looks like they were made by heavy boots worn " +
              "by heavy human warriors.\n"));

    add_exit("f7", "northeast");
    add_exit("ran/ran5", "west");
    add_exit("fe", "southeast");
}
