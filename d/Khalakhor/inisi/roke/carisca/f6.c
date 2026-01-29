/*
 * f6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object grugg;

void reset_room();

int
block_me ()
{
  TP->catch_msg("A wooden boom cuts the access to the clearing. "+
                "You read the label <MARINERS OF GENESIS> on the boom.\n");
  return 1;
}

void
create_room()
{
    set_short("Forest on Carisca island");
    set_long("The forest around you is quite dark and damp. The " +
             "trees seem to reach out for you and you hear the " +
             "mating roars of the wild boars in the distance. " +
             "This room is exactly like the rest of the island, " +
             "except for the footprints on the ground going towards " +
             "a small hole in the ground. To the west you notice a "+
             "clearing and a patch of turquoise.\n");

    add_item(({"prints", "footprints"}),
             "The footprints are very large here, but seems to shrink when " +
             "they approach the hole.\n");
    add_item("hole", "The hole is too small to be entered.\n");
    add_cmd_item("hole", "enter", "You don't fit.\n");

    add_exit("f4", "north");
    add_exit("pier-mariners", "west", block_me);
    add_exit("f8", "south");
    
    reset_room();
}

void
reset_room()
{
    if (grugg)
        return;

    grugg = clone_object(ROKEDIR + "npc/grugg");
    grugg->move(TO);
    tell_room(TO, "A nasty grugg arrives.\n");
}
