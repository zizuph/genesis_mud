/*
 * f2.c
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
    set_long("You have moved rather deep into the forest. Around you " +
             "are lots of trees and in the distance you can hear some " +
             "birds singing. A small track leads north, deeper into " +
             "the forest.\n");

    TREE2;
    BIRDS;

    add_exit("f5", "north");
    add_exit("f1", "southeast");
}
