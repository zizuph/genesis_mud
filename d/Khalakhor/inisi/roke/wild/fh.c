/*
 * fh.c
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
    set_short("Forest");
    set_long("This is the heart of a big forest. The trees are high " +
             "above you and you feel a little afraid as you walk " +
             "through the darkness. Something tells you that you might " +
             "not be completely alone. The path leads west and northeast " +
             "from here.\n");

    TREES;
    TREE1;

    add_exit("fi", "northeast");
    add_exit("fg", "west");

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
