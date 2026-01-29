/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stairs2.c
 *
 * A staircase
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
    return ({LOD_DIR + "monster/bat"});
}
public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2"});
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Staircase");
    set_long("You are standing at the lower end of the stairs. " +
	     "There is an opening in the stone wall to the south.\n");

    add_item(({"wall", "walls"}), "The walls are made out of large " +
	     "stones. The stones must have been cut by an expert, since " +
	     "there are almost no gaps between them.\n");

    add_item(({"gap", "gaps"}), "Small amounts of dirty water emerges " +
	     "from the gaps.\n");

    /* add_item opening */
    
    add_exit(LOD_DIR + "stairs1",     "up",    0);
    add_exit(LOD_DIR + "guard_room1", "south", 0);

    reset_room();
}
