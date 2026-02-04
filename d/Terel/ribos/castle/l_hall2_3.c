/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall2_3.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "hall_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/stronguard"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() +  "It continues " +
	     "to the south.  You can smell pleasant things to your " +
	     "east, and unpleasant things to your north.\n");

    add_exit(CASTLE_DIR + "r_bath2",   "north", 0);
    add_exit(CASTLE_DIR + "study",     "west",  0);
    add_exit(CASTLE_DIR + "harem",     "east",  "@@guarded");
    add_exit(CASTLE_DIR + "l_hall2_2", "south", 0);

    reset_room();
}

/*
 * Function name: guarded
 * Description:   Don't let player pass if guards are present
 * Returns:       1
 */
public int
guarded()
{
    if(!present("knight"))
	return 0;
    
    write("As you attempt to enter the harem, the Knight halts " +
	  "your progress.\n");
    return 1;
}

