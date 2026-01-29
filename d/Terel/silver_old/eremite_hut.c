/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * eremite_hut.c
 *
 * This is a hut for an eremite. Mortricia 920717
 * Modified by Sorgum 921002
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({SILVER_DIR + "monster/eremite"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("A ramshackle hut");
    set_long("You are inside a very old hut. It must be decades since " +
	     "anyone bothered to repair it, and you notice that " +
	     "the walls might tumble down on you any minute.\n");

    add_item(({"wall", "walls"}), "There is a window in one of the walls.\n");
    add_item(({"window"}), "You wonder why a hut like this has a window.\n");

    INSIDE;

    add_exit(SILVER_DIR + "forest25", "west", 0);
    reset_room();
}
