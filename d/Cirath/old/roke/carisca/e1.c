/*
 * e1.c
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
    set_long("You are high up in the air on the edge of a steaming " +
             "volcano. Below you, to the south you see a boiling lake " +
             "of lava, and strangely enough, a high stone pillar placed " +
             "in the middle of the lava.\n");

    add_item("pillar",
             "It stands in the middle of the lava lake. There is " +
             "something on the top of it.\n");

    add_exit("l1", "south", "@@block");
    add_exit("e2", "east");

    reset_room();
}

int
block()
{
    if (!(TP->query_prop(COLDFEET)))
    {
        TP->catch_msg("The lava is too hot!\n");
        return 1;
    }
    TP->add_prop(COLDFEET, 1);
    return 0;
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
