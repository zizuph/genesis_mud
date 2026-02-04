/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * knight_room.c
 *
 * A generic knight room in the Ribos castle.
 *
 * Vader
 * Recoded by Sorgum 950708
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

create_room()
{
    ::create_room();
    set_short("Knights quarters");
    set_long("You have entered a large room.  This is where the " +
	     "kings most honorable knights stay.  There is nothing " +
	     "here except a bed, and a mannequin to store platemail.\n");

    add_item(({"bed"}), "A simple, single size bed.  Nothing special here.\n");

    add_item(({"mannequin"}), "It is really just a wooden stick figure " +
    "of a human that holds armour.\n");

    INSIDE;
}

