/*
 * e3.c
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
    set_short("on the edge of a volcano");
    set_long("Below you a small path leads down to a thick forest, " +
             "and to the west you can see a thin stone pillar standing " +
             "in the middle of a boiling lava lake.\n");

    add_exit("p", "down");
    add_exit("e2", "north");
    add_exit("e5", "south");

    add_item("pillar",
             "There is something strange on the top of the pillar.\n" +
             "Unfortunately you are not close enough to get a good look at it.\n");

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
