/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave16.c
 *
 * The home of the red dragon.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ORC_CAVE_DIR + "monster/red_dragon"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() +
	     "The walls are covered with deep marks from the dragon " +
	     "that lives here.  " +
	     "An old and evil creature with many lives on its conscience.\n");
    
    DARK;
    
    add_exit(ORC_CAVE_DIR + "cave11", "west");
    reset_room();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "It smells like a sulfur furnace from hell in here!\n";
}
