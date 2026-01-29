/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guard_room2.c
 *
 * A guard room for the legion Redhawk 92 09 22
 * Modified by Sorgum 941025
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
    return ({LOD_DIR + "monster/dark_guard"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Guard room");
    set_long("You are standing in something that looks like a guard room. " +
	     "there is a banner over the south exit that reads " +
	     "THE LEGION OF DARKNESS OFFICER QUARTERS\n");

    add_item(({"banner"}), "Its a banner colored in black and red.\n");

    add_exit(LOD_DIR + "tunnelr7", "north", 0);
    add_exit(LOD_DIR + "corr20",   "south", 0);

    reset_room();
}
