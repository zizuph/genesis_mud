/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * r_bath.c
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
                 CASTLE_DIR + "monster/okayguard"
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
	     "the two longest walls there are single beds, " +
	     "covered by a soft mattresses and pink and lavender " +
	     "covers.  There must be about 50 of them.  Next to " +
	     "each bed is a small night table.  It is quite " +
	     "obvious that the female servants sleep here.  Light " +
	     "comes from many candles.\n");
 
    add_item(({"bed", "beds", "mattress", "mattresses", "covers"}), 
	     "With a definite feminine touch, these items are " +
	     "among the most luxurious items you've ever seen provided for " +
	     "'the help'.  The bed frame is of fine wood, with soft " +
	     "colourful bedsheets.  It must be very good to work " +
	     "for this royal family.\n");
 
    add_item(({"night table", "night tables", "table", "tables"}), 
	     "These are just simple tables, with a small drawer.  " +
	     "The drawer is protected by magic so that only the " +
	     "proper person can open it.\n");
 
    add_item(({"candle", "candles"}), "You see nothing special.\n");
 
    INSIDE;

    reset_room();
    add_exit(CASTLE_DIR + "l_hall2_1", "east", 0);
}
 
