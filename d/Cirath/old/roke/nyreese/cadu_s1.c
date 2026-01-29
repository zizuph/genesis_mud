/*
 * cadu_s1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object sailor,lisa;

void
checklisa()
{
    if (!lisa)
    {
	lisa = clone_object(ROKEDIR + "npc/girl");
	lisa->move_living("from a house", TO);
    }
    set_alarm(700.0, 0.0, checklisa);
}

void
reset_room()
{
    if (sailor) return;

    sailor = clone_object(ROKEDIR + "npc/sailor");
    sailor->move(TO);
    tell_room(TO , "A drunken sailor arrives.\n");
}

void
create_room()
{
    set_short("Shore");
    set_long("You have arrived at the southmost parts of Cadu.\n" +
	     "To the south is a pier and to the east and west the " +
	     "shore continues for what seems like an eternity. " +
	     "It looks like the fishermen's harbour to the west. " +
	     "To the north are the central parts of Cadu.\n");

    add_exit("cadu_p1", "north");
    add_exit("cadu_b1", "south");
    add_exit("cadu_s2", "west");
    add_exit("cadu_s5", "east");

    BEACH;

    seteuid(getuid(TO));
    
    reset_room();
    set_alarm(35.0, 0.0, checklisa);
}

