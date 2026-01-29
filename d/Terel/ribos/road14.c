/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road14.c
 *
 * A road in Ribos
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
    set_short("A smooth dirt road");
    set_long("You are travelling a dirt road.  This " +
	     "road leads west to an intersection and east to the bank.\n");

    add_exit(RIBOS_DIR + "intsec3", "west", 0);
    add_exit(RIBOS_DIR + "road11",  "east", 0);
}

