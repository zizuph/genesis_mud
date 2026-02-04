/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * klounge.c
 *
 * Vader
 * Recoded by Sorgum 950602
 *
 *  Modified, 3 May 2003, by Bleys
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
    set_short("Knights lounge");
    set_long("Covering the stone walls of this chamber are fabulous murals " +
	     "and paintings depicting Ribos' knights fighting all sorts of " +
	     "foes. The chamber is furnished with nice chairs, couches, " +
	     "and tables. Decorating the room are many suits of armour, " + 
	     "these being for show. The room has no windows, and is lit by " +
	     "many candles.\n");

    add_item(({"couches", "couch", "chairs", "table", "tables", "chair"}), 
	     "They are quite comfortable, and only slightly worn.\n");

    add_item(({"paintings", "murals", "mural", "painting"}),
	     "You see nothing special, besides the spectacular job the " +
	     "painter did.\n");

    add_item(({"candle", "candles"}),
	     "You see nothing special about the candles.\n");

    add_item(({"armour", "suit of armour", "suits of armour"}), 
	     "These are very fine pieces, finely polished, showing off " +
	     "the true nobility of the men who wear them.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "l_hall1_5", "southeast", 0);
    add_exit(TOWER_DIR + "nw_tower1",  "northwest", 0);

    reset_room();
}
