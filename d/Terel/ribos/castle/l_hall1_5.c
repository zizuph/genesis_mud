/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall1_5.c
 *
 * Vader
 * Recoded by Sorgum 950602
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
    object door;

    ::create_room();

    set_long("This is a large, regal hallway.  It is decorated by " +
	     "paintings and busts of great people.  It continues east " +
	     "and southwest.\n"); 

    add_exit(CASTLE_DIR + "l_hall1_6", "east",      0);
    add_exit(CASTLE_DIR + "l_hall1_4", "southwest", 0);
    add_exit(CASTLE_DIR + "klounge",   "northwest", 0);
    
    clone_object(DOOR_DIR + "knight8_in")->move(TO);            
}
