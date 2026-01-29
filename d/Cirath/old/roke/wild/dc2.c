/*
 * dc2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object dragon;

void
reset_room()
{
    if (dragon)
        return;

    dragon = clone_object(ROKEDIR + "npc/bluedragon");
    dragon->move(TO);
}

void
create_room()
{
    set_short("large dark cave");
    set_long("You are inside a dark damp cave. It looks a little unpleasant " +
             "here, and a foul smell is in the air.\n");

    DARK;
    INSIDE;

    add_exit("dc1", "north", "@@block");
    add_exit("dc3", "south");

    reset_room();
}

int
block()
{
    if (MAL("dragon"))
    {
        write("The dragon blocks your way.\n");
        return 1;
    }
    return 0;
}
