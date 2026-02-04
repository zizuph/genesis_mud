/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * r_hall2_1.c
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
    set_long(query_long() +
	     "It continues northwards.  There is a library to your east, " +
	     "and the fresh air of Ribos can be breathed " +
	     "to your southwest.\n");
    
    add_exit(CASTLE_DIR + "land2_3",   "southwest", 0);
    add_exit(CASTLE_DIR + "r_hall2_2", "north",     0);
    add_exit(CASTLE_DIR + "library",   "east",      0);    
}
