/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road10.c
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
    return ({RIBOS_DIR + "monster/w_knight",
	     RIBOS_DIR + "monster/w_knight"});		 
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
    set_long("You are on a dirt road leading south towards " +
	     "the Bank.  To the north is the intersection, and to your west " +
	     "stands a house that appears to still be in use.  To the east, " +
	     "there is a large field with sheep grazing.\n");

    add_item(({"fields"}), "Large patches of grass are what feed the " +
             "sheep that are grazing here.\n");

    add_item(({"house"}), "It looks like it was abandoned in a hurry.\n");

    add_exit(RIBOS_DIR + "intsec2", "north", 0);
    add_exit(RIBOS_DIR + "road11",  "south", 0);
    add_exit(RIBOS_DIR + "house7",  "west",  0);
}

