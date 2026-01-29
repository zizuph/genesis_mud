/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * war1w.c
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
    set_short("An empty room");
    set_long("You are standing in an empty room, it looks a bit strange " +
	     "you wonder what this room could be used for?\n");

    add_item(({"walls"}), "Just ordinary walls, they seem to be darkened " +
	     "by something though.\n");

    add_item("floor", "Just an ordinary floor, but it seems to be darkened " +
	     "by something!\n");
    add_item(({"roof", "ceiling"}), "Just an ordinary ceiling, but it " +
	     "seems to be darkened by something!\n");

    add_exit(LOD_DIR + "war1.c", "east", 0);

    reset_room();
}
