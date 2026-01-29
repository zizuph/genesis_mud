/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hall.c
 *
 * A big hall in LoD.
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
    return ({LOD_DIR + "monster/master_knight"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A giant hall in the legion quarters");
    set_long("You are standing in a big hall that belongs to the legion " +
	     "of darkness there's a table in the middle of the room with " +
	     "some chairs at it.  On the walls there are paintings of " +
	     "old battles that the legion have fought.\n");

    add_item(({"table"}), "It is a large wooden table for many people.  " +
	     "You realize that the legion members gather here for " +
	     "meetings and for joy.\n");
    
    add_item(({"wall", "walls"}), "The walls are filled with paintings " +
	     "of old forgottened battles.\n");

    add_item(({"painting", "paintings"}), 
	   "It's a big painting with a large man that is sitting on a horse " +
	   "killing everything that comes in his way.  You realise that " +
	   "this must be one of the three ancient leaders of the legion " +
	   "of darkness they who have been spreading darkness over the " +
	   "world since time began.\n");

    add_exit(LOD_DIR + "corr6.c",    "north", 0);
    add_exit(LOD_DIR + "war1.c",      "south", 0);    
    add_exit(LOD_DIR + "corr17",     "east",  0);
    add_exit(LOD_DIR + "tunnelr1.c", "west",  0);

    reset_room();
}
