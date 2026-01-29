/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road9.c
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
    set_long("You are on a dirt road leading south " +
	     "towards the Post Office.  To your east, there is what " +
	     "remains of a house.  It is in pieces now, totally " +
	     "crushed into rubble.  You wonder what force could " +
	     "have done that!\n");

    add_item(({"house", "rubble"}), "Only something VERY powerfull " +
             "could have done this.  The largest piece of rubble is the " +
             "size of your fist.\n");

    add_exit(RIBOS_DIR + "intsec1", "north", 0);
    add_exit(RIBOS_DIR + "road12",  "south", 0);
}

