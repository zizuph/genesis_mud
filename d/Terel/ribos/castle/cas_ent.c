/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cas_ent.c
 *
 * Ribos Castle entrance
 *
 * Vader
 * Recoded by Sorgum 950602
 *
 *
 * Modified 3 May 2003, by Bleys
 *     - removed newline from the short desc
 *
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/c_guard",
	     CASTLE_DIR + "monster/c_guard"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Castle Entrance");
    set_long("You are at the entrance to the Castle of Ribos.  " +
	     "There are guard quarters to the east and west, and " +
	     "the intersection is to the south.\n");

    add_item(({"castle"}),
	     "It is splendid looking.  Truly a castle fit for a king.\n");

    add_exit(CASTLE_DIR + "gate_ent",   "north", 0);
    add_exit(RIBOS_DIR + "intsec4",     "south", 0);
    add_exit(CASTLE_DIR + "g_quart1_1", "east",  0);
    add_exit(CASTLE_DIR + "g_quart1_2", "west",  0);

    INSIDE;
    reset_room();
}

