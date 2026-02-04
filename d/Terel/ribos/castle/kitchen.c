/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * kitchen.c
 *
 * Vader
 * Recoded by Sorgum 950602
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo
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
    return ({CASTLE_DIR + "monster/cook",
		 CASTLE_DIR + "monster/boy"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Kitchen");
    set_long("You are in a very modern looking room.  It is " +
	     "surrounded by nice looking shelves, where all " +
	     "kinds of foodstuffs are kept. This is where the " +
	     "king's meals are prepared.\n");

    add_item(({"shelf", "shelves"}),
	     "They are made of wood, and contain flour, cornmeal, various " +
	     "preserved foods\nheld in jars, and spices from around " +
	     "the world.\n");
    
    add_item(({"food", "foodstuff", "foodstuffs"}),
	     "You see flour, cornmeal, various jarred vegetables, " +
	     "and spices.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "dining_room", "east", 0);

    reset_room();
}
 
