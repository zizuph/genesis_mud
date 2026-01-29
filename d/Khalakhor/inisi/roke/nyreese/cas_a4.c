/*
 * cas_a4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object rat;

void
reset_room()
{
    if (rat) return;

    rat = clone_object(ROKEDIR + "npc/rat");
    rat->move(TO);

    tell_room(TO, "A black rat arrives through a hole in the wall.\n");
}

void
create_room()
{
    set_short("First floor of the Castle");
    set_long("You are standing in a damp room with stone walls. To the " +
             "northeast is the entrance to one of the towers.\n");

    add_exit("cas_a8",  "south");
    add_exit("cas_t12", "northeast");
    INSIDE;
    add_item("walls", "They bear signs of recent battles.\n");

    reset_room();
}
