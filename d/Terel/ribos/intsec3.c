/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * intsec3.c
 *
 * An intersection in Ribos
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
    set_short("A smooth dirt intersection");
    set_long("You are at a dirt intersection.  There are " +
	     "roads heading in all four directions.  To the north, " +
	     "you can see the town square.  To the south, the road " +
	     "ends at the entrance to some caves.\n");

   add_item(({"caves", "cave"}), "This cave is closed off by a HUGE " +
            "iron plate, permanantly placed\nover the entrance.\n");

   add_item(({"square"}), "You can barely see it from here, but you " +
            "can tell that it is deserted.\n");

   add_exit(RIBOS_DIR + "road4",  "north", 0);
   add_exit(RIBOS_DIR + "road15", "south", 0);
   add_exit(RIBOS_DIR + "road13", "west",  0);
   add_exit(RIBOS_DIR + "road14", "east",  0);
}

