/*
 * f6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object grugg;

void reset_room();

void
create_room()
{
    set_short("Forest on Carisca island");
    set_long("The forest around you is quite dark and damp. The " +
             "trees seem to reach out for you and you hear the " +
             "mating roars of the wild boars in the distance. " +
             "This room is exactly like the rest of the island, " +
             "except for the footprints on the ground going towards " +
             "a small hole in the ground.\n");

    add_item(({"prints", "footprints"}),
             "The footprints are very large here, but seems to shrink when " +
             "they approach the hole.\n");
    add_item("hole", "The hole is too small to be entered.\n");
    add_cmd_item("hole", "enter", "You don't fit.\n");

    add_exit("f4", "north");
    add_exit("f8", "south");
    reset_room();
}

void
reset_room()
{
    if (grugg)
        return;

    grugg = clone_object(ROKEDIR + "npc/grugg2");
    grugg->move(TO);
    tell_room(TO, "A nasty grugg arrives.\n");
}
