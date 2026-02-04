/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * r_hall1_4.c
 *
 * Vader
 * Recoded by Sorgum 950708
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
    set_long(query_long() + "It continues " +
	     "south and northwest.  There is a door to the east\n");

    add_exit(CASTLE_DIR + "r_hall1_3", "south",     0);
    add_exit(CASTLE_DIR + "r_hall1_5", "northwest", 0);

    clone_object(DOOR_DIR + "knight4_in")->move(TO);        
}
