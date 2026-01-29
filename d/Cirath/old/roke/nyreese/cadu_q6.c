/*
 * cadu_q6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object boy;

void
reset_room()
{
    if (!boy)
    {
        boy = clone_object(ROKEDIR + "npc/boy");
        boy->equip_me();
        boy->move(TO);
    }
}

void
create_room()
{
    set_short("Town square");
    set_long("You are at the town square in Cadu. " +
             "To the north you see a the rubble of a " +
             "burned down hut. To the west you sense a " +
             "field of great magic.\n");
    
    add_item("building", "It's obviously the bank of Cadu.\n");

    add_exit("cadu_q5", "west");
    add_exit("cadu_q3", "south");
    add_exit("cadu_q9", "north");
    add_exit("cadu_casino", "east");

    reset_room();
}
