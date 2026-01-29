/*
 * red_r3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object m;

void reset_room();

void
create_room()
{
    set_short("on a small road");
    set_long("This is a small road leading along the shore. " +
             "Around you you spot various bushes and other vegetation " +
             "and somewhere inside the trees you hear a few birds. " +
             "There are some old buildings west of here. " +
             "You recognize the rest of Cadu east of you.\n");

    add_item("bushes",
             "The bushes are quite green. (Did you expect something else?)\n");
    add_item("vegetation",
             "The vegetation consists mostly of old, brown grass.\n");
    add_item("birds", "The birds are so far away that you can't see them.\n");

    add_exit("red_r2", "west");
    add_exit("cadu_a5", "east");
    add_exit("red_r4", "south");

    reset_room();
}

void
reset_room()
{
    if (!m)
    {
        m = clone_object(ROKEDIR + "npc/moralist");
        m->move(TO);
    }
}
