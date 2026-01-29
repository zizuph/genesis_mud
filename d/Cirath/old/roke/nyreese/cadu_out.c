/*
 * cadu_out.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object bard, waiter, vh;

void
reset_room()
{
    if (!objectp(bard))
    {
	bard = clone_object(ROKEDIR + "npc/bard");
	bard->move_living("xxx", TO);
    }
    if (!objectp(waiter))
    {
	waiter = clone_object(ROKEDIR + "npc/waiter");
	waiter->move_living("xxx", TO);
    }
    if (!objectp(vh))
        {
	vh = clone_object(ROKEDIR + "npc/van_helsing");
        vh->equip_me();
	vh->move_living("xxx", TO);
    }
}

void 
create_room()
{
    set_short("Open air cafe");
    set_long("You are at an open air cafe close to the bustling " +
             "town square of Cadu. You see a few free tables with nice " +
             "looking chairs around them. There are lots of people drinking " +
             "beer in the warm sun.\n");

    add_item("people",
             "They are citizens of Cadu. Almost everyone sits on a chair.\n");
    add_item((({"chair", "chairs"})),
             "The wooden chairs look pretty comfortable.\n");
    add_item(({"table", "tables"}),
             "Just some standard tables. They look quite new though.\n");

    OUTSIDE;

    add_exit("cadu_inn","north");
    add_exit("cadu_q4", "east");

    reset_room();
}
