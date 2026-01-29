/*
 * f1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
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
    set_long("You are standing just outside the city of Cadu. " +
             "Around you are quite a lot of trees. You realize that " +
             "you are at the edge of a large forest.\n");

    TREES;
    TREE1;

    add_exit("f2", "northwest");
    add_exit(NYREESEDIR + "cadu_a7", "southwest");
    add_exit("f3", "northeast");
}
