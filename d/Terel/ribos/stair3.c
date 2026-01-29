/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stair3.c
 *
 * Staircase to Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("An ancient staircase");
    set_long("You are on an ancient staircase, carved from stone " +
	     "eons ago.  You start\nto wonder just how tall that cliff " +
	     "really is.\n");

    add_item(({"stair", "stairs", "staircase"}),
	     "It looks like it has seen years of use\n");

    add_exit(RIBOS_DIR + "stair4", "down", 0);
    add_exit(RIBOS_DIR + "stair2", "up",   0, 3);
}
