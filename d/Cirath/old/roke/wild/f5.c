/*
 * f5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
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

    add_exit("ran/for1", "north");
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
    set_alarm(120.0, 0.0, &reset_room()); //?? FIXA
}
