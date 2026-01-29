/*
 * cas_a12.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Outside the southeast tower");
    set_long("You are standing in a small room, just outside " +
             "the southeast tower. Lots of old armour and weapons " +
             "are stashed away at the sides of the room, and you " +
             "quickly decide that this must be the armoury of the " +
             "castle.\n");
    
    add_item(({"weapon", "weapons"}), "The weapons are old and useless.\n");
    add_item(({"armour", "armours"}),
             "The armours are very rusty and cannot be used.\n");

    add_exit("cas_a8",  "north");
    add_exit("cas_t14", "southeast");
}
