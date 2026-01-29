/*
 * fk.c
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
    set_short("Forest edge");
    set_long("You are on the eastern edge of the large forest. To the north " +
             "you see a small road. Back west you hear noises from a woodpecker. " +
             "To the east you can spot some mountains in the distance.\n");

    TREES;
    TREE1;

    add_exit("fl", "north");
    add_exit("fj", "west");
}
