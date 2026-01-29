/*
 * f5.c
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

object snail;

void reset_room();

void
create_room()
{
    set_short("Sunny meadow");
    set_long("This is a sunny meadow in an opening between some of the trees. " +
             "You are surrounded by trees, which seem inhabitated by birds, " +
             "and below you on the ground grows some grass.\n");

    BIRDS;
    TREES;
    TREE2;
    GRASS;

    add_exit("ran/ran1", "north");
    add_exit("f2", "south");

    reset_room();
}

void
reset_room()
{
    if (snail)
        return;

    snail = clone_object(ROKEDIR + "obj/snail");
    snail->move(TO);
    tell_room(TO, "A wet snail arrives.\n");
    enable_reset(200);
}
