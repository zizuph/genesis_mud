/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall_6.c
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
    set_long("This is a large, regal hallway.  It is decorated by " +
	     "paintings and busts of great people.  It continues " +
	     "east and west.\n");
    
    add_exit(CASTLE_DIR + "m_hall1_2", "east", 0);
    add_exit(CASTLE_DIR + "l_hall1_5", "west", 0);

    clone_object(DOOR_DIR + "knight7_in")->move(TO);
    
    reset_room();
}
