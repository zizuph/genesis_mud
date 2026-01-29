/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave09.c
 *
 * A cave room that is home to two orc guards.
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
    return ({ORC_CAVE_DIR + "monster/orcguard",
	     ORC_CAVE_DIR + "monster/orcguard"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "\n");
    
    DARK;
    
    add_exit(ORC_CAVE_DIR + "cave08", "south");
    add_exit(ORC_CAVE_DIR + "cave10", "southeast");
    add_exit(ORC_CAVE_DIR + "cave13", "east");
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
    return "There is a smell of foul creatures.\n";
}
