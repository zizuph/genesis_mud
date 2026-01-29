/*
 * f8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

object shepherd;

#include "defs.h"

void
reset_room()
{
    if (!objectp(shepherd))
    {
        shepherd = clone_object(ROKEDIR + "npc/shepherd");
        shepherd->move_living("X", TO);
    }
}

void
create_room()
{
    set_short("Forest");
    set_long("You are on a small track on the northern edge of the forest. " +
             "There is lots of high grass streching north towards the " +
             "mountains far away. South you see the thick and dark forest. " +
             "You can also hear sounds from animals.\n");

    add_item("grass", "It's ordinary green grass.\n");

    add_exit("f7", "south");
    add_exit("f9", "east");
    reset_room();
}
