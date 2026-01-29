/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road8.c
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
	     "somewhere beneath it.  To your east, you can see many " +
	     "small fields where food is grown for the citizens.  There " +
	     "are also farmhouses, but they are unreachable from " +
	     "here.\n");


    add_item(({"fields"}), "Small patches of wheat and corn spread " +
             "out across the land, all in dire need of harvesting.  " +
             "You wonder where the farmers might be....\n");

    add_item(({"house", "houses", "farms", "farmhouses"}), 
	     "These houses are slowly being reclaimed by the weeds and " +
	     "tall grass.\n");


    add_item(({"castle"}), "You can see it pretty well from here, " +
             "and you notice that it is not run down, like the rest of " +
             "Ribos.\n");

    add_exit(RIBOS_DIR + "intsec4", "west",  0);
    add_exit(RIBOS_DIR + "road6",   "south", 0);

}

