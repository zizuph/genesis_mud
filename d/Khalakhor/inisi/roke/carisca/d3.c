/*
 * d3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object ghoo;

void reset_room();

void
create_room()
{
    set_short("A cosy stone chamber");
    set_long("You have entered the throne room of the old dwarf city.\n" +
             "This is the place where the dwarf king used to hold his " +
             "audiences, and rumors say that he is haunting the room " +
             "to be able to guard the treasures in the treasure chamber " +
             "south of here.\n");

    add_exit("d2", "west");
    add_exit("d5", "south", "@@block");
    reset_room();
}

int
block()
{
    if (!MAL("ghost"))
        return 0;

    say(QCTNAME(TP) + " tries to walk south but is stopped by the ghost.\n");
    write("You try to go south but the ghost stops you!\n");

    return 1;
}

void
reset_room()
{
    if (objectp(ghoo))
        return;

    /* load treasurechest */

    (CARISCADIR + "d5")->load_chest();

    ghoo = clone_object(ROKEDIR + "npc/kingghost");
    ghoo->equip_me();
    ghoo->move(TO);
    tell_room(TO, "A ghost materializes before you.\n");
}
