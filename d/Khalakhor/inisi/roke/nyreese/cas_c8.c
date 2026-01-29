/*
 * cas_c8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object guard;

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This room looks more like a corridor. The walls are draped " +
             "with black, silk curtains. The light from the ceiling is a " +
             "bit stronger here.\n");

    add_exit("cas_c4", "north");
    add_exit("cas_c12", "south");

    add_item(({"curtain", "curtains"}),
             "The black curtains looks heavy. As you try to touch them" +
             " they move away from you... Another magical trick.\n");
    reset_room();
}

void
reset_room()
{
    if (guard)
        return;

    guard = clone_object(ROKEDIR + "npc/knights");
    guard->equip_me();
    guard->move(TO);
    tell_room(TO, "A knight in armour steps out of the curtains.\n");
}
