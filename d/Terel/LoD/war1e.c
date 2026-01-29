/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * war1e.c
 *
 * a room for the legion Redhawk 920921 
 * Modified by Sorgum 941029
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "monster/steel_guard"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A map room");
    set_long("You are standing in a storage room where the legion keeps " +
	     "their maps and tactical documents.  There is a table in " +
	     "the middle of the room.\n");

    add_item(({"maps"}), "The maps that have many different marks and " +
	     "symbols on them.\n");

    add_item(({"table"}), "It's a sturdy table with lot of maps on it.\n");
    
    add_exit(LOD_DIR + "war1.c", "west", 0);

    reset_room();
}
