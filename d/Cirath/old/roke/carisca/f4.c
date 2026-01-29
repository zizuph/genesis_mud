/*
 * f4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>

void
create_room()
{
    set_short("Forest on Carisca island");
    set_long("The forest around you is quite dark and damp. The " +
             "trees seem to reach out for you and you hear the " +
             "mating roars of the wild boars in the distance. High " +
             "above you are the mighty branches of a huge tree that " +
             "looks climbable.\n");

    add_item("tree", "The tree has thick and solid branches.\n");

    add_exit("f1", "north");
    add_exit("f6", "south");
}

int
climb(string s)
{
    NF("Climb what?\n");
    if (s != "tree" && s != "the tree")
        return 0;

    NF("You try to climb the tree, but fail.\n");
    if (TP->query_skill(SS_CLIMB) <= random(10))
        return 0;

    TP->move_living("climbing the tree", CARISCADIR + "tree1");
    return 1;
}

void
init()
{
    ::init();

    add_action(climb, "climb");
}
