/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road3.c
 *
 * A road in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: query_moving_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({RIBOS_DIR + "monster/child"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A smooth dirt road");
    
    set_long("You are on a dirt road south of the square.  It looks as " +
	     "if it was once smooth, but in a few places, potholes have " +
	     "marred the surface.  You know Ribos is known for its " +
	     "peacefullness, and you are puzzled as to why it seems " +
	     "deserted.  What could have scared the people off?  To " +
	     "the west is a Blacksmith and east of here is a small " +
	     "public building of some sort.\n");

    add_item(({"blacksmith", "blacksmith shop", "shop"}),
	     "This shop looks better than the rest of the buildings. " +
	     "Perhaps it's open.\n");

    add_item(({"building", "public building", "small building"}),
	     "This is where Ribos citizens posted major announcements.\n");

    add_exit(RIBOS_DIR + "square", "north", 0);
    add_exit(RIBOS_DIR + "road4", "south", 0);
    reset_room();
}

