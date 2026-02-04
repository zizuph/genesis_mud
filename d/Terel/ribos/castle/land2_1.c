/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * land2_1.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "landing_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() +
	     "To your west, through an archway, you see a chapel.  " +
	     "That is where the royal family does most of its " +
	     "worship, although they do attend the Ribos " +
	     "church from time to time, when they wish to make a public " +
	     "appearance.\n");
    
    add_item(({"archway"}), "It is a simple stone archway.\n");

    add_item("chapel", "Why don't you go in?\n");

    add_exit(CASTLE_DIR + "court",     "down", 0);
    add_exit(CASTLE_DIR + "land3_1",   "up", 0);
    add_exit(CASTLE_DIR + "land2_2",   "east", 0);
    add_exit(CASTLE_DIR + "chapel",    "arch", 0);
    add_exit(CASTLE_DIR + "l_hall2_1", "west", 0);
}
