/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * quarters.c
 *
 * Generic quarters for legion of darkness.


    Modified: 15 Sep 2003, by Bleys
        - Modified the bed add_item to use the query_rank() return as
            a plural, like set_long and set_short do.
        - Modified the default return of query_rank() to be plural.

 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

/*
 * Function name: query_rank
 * Description:   the rank in the army who lives in these quarters.
 * Returns:       a string that is the rank.
 */
public string
query_rank()
{
    return "grunts";
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Private quarters for the " + query_rank() + " in the legion");
    set_long("It's the private quarters for the " + query_rank() + " in " +
	     "the army of the legion of darkness. There is a table and some " +
	     "beds standing here that seem recently used.\n");

    add_item(({"bed", "beds"}),
        "They are comfortable beds that the " + query_rank() + " use " +
	     "when they are not on duty.\n");
    
    add_item(({"wall", "walls"}), "It's a wall with a painting on it.\n");

    add_item(({"painting", "paintings"}),
	     "It's a painting of the leader of this sub division of " +
	     "the legion.\n");
    
    add_item(({"table"}), "It's a sturdy dinner table made of wood.\n");
}
