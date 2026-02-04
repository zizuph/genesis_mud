/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall2_1.c
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
    return ({CASTLE_DIR + "monster/boy"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "It continues north and south.  To your " +
	     "west, you sense a musty odor.\n");

    add_exit(CASTLE_DIR + "l_hall2_3", "north", 0);
    add_exit(CASTLE_DIR + "l_hall2_1", "south", 0);
    add_exit(CASTLE_DIR + "m_beds",    "west",  0);

    reset_room();
}
