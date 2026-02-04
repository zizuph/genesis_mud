/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall3_1.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "hall_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "It continues northward.  East will " +
	     "take you outside.\n");
    add_exit(CASTLE_DIR + "l_hall3_2", "north", 0);
    add_exit(CASTLE_DIR + "land3_1",   "east", 0);
}
