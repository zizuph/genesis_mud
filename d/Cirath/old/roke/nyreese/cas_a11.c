/*
 * cas_a11.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged & Gresolle */

/* this is the room in which the players arrive when pressing the
   magic button of the statues */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    INSIDE;

    set_short("Entrance room");
    set_long("You find yourself standing inside a small room in a " +
             "rather large stone building. The walls are shimmering " +
             "in a faint blue color. Your sensitive mind detects the " +
             "presence of ancient magic...\n");

    add_item("walls", "The walls are shimmering from a powerful forcefield.\n");

    add_exit("cas_a7",  "north");
    add_exit("cas_a10", "west");
}


