/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road5.c
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

    set_long("You are on a dirt road leading to the Castle of Ribos.  " +
	     "This is where King Bor-El lives, and it is also " +
	     "rumoured that the great wizard Vader has his chambers " +
	     "somewhere beneath it.  To your east is an old run down " +
	     "house.  Its door is open, and you think you hear noises " +
	     "from within.  There is a pub further north but you start " +
	     "to wonder if it is open.\n");

    add_item(({"building", "house", "run down house"}),
	     "It looks pretty run down!  Perhaps you should investigate.\n");

    add_exit(RIBOS_DIR + "road7",   "north", 0);
    add_exit(RIBOS_DIR + "intsec1", "south", 0);
    add_exit(RIBOS_DIR + "house5",  "east",  0);

}

