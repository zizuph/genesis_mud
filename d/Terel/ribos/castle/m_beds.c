/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * m_beds.c
 *
 * Vader
 * Recoded by Sorgum 950712
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
    return ({CASTLE_DIR + "monster/weakguard",
                 CASTLE_DIR + "monster/weakguard",
                 CASTLE_DIR + "monster/weakguard"
                 });		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Bunk room");
    set_long("You have entered a barracks style bunk room.  Along " +
	     "the two longest walls there are single cots, covered " +
	     "by coarse, scratchy, grey covers.  There must be about " +
	     "30 of them.  It is quite obvious that those who sleep " +
	     "here don't get a very good nights sleep.  Beside each " +
	     "bed is a small night table.  Light comes from many " +
	     "candles.\n");
 
    add_item(({"cot", "cots", "covers"}), 
	     "You can tell that those that sleep here itch alot at night.\n");
 
    add_item(({"night table", "night tables", "table", "tables"}), 
	     "These are just simple tables, with a small drawer.  " +
	     "The drawer is protected by magic so that only the proper " +
	     "person can open it.\n");
 
    add_item(({"candle", "candles"}), "You see nothing special.\n");

    INSIDE;

    reset_room();
 
    add_exit(CASTLE_DIR + "l_hall2_2", "east", 0);
}
 
