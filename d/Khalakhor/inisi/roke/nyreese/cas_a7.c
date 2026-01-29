/*
 * cas_a7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged & Gresolle */
/* a room in the castle serving as starting location for the walkin' knight */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object knight; /* this global is automagically set to NULL when knight dies */

void
create_room()
{
    INSIDE;

    set_short("Inside the Castle");
    set_long("You are standing somewhere in the middle of the huge " +
             "castle of Cadu. To the north you can vaguely spot " +
             "a staircase.\n");

    add_exit("cas_a3",  "north");
    add_exit("cas_a8",  "east");
    add_exit("cas_a11", "south");

    reset_room();
}

void
reset_room()
{
    if (knight) return; /* he's not dead, we don't want the castle full of 'em */

    knight = clone_object(ROKEDIR + "npc/knights");
    knight->equip_me();
    knight->move(TO);
}
