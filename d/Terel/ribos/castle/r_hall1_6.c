/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * r_hall1_6.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "hall_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/weakguard"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "It continues east and west.  " +
	     "There is a door to the north.\n");
    
    add_exit(CASTLE_DIR + "r_hall1_5", "east", 0);
    add_exit(CASTLE_DIR + "m_hall1_2", "west", 0);

    clone_object(DOOR_DIR + "knight6_in")->move(TO);
    
    reset_room();
}
