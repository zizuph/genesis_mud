/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * square.c
 *
 * Ribos Town Square
 *
 * Vader
 * Recoded by Sorgum 950602
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo
 *  Modified: 29 June 2007 by Lilith
 *      - reopened shop
 *
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
    set_short("Ribos town square");
    
    set_long("The beauty of this square, which is the center of the common " + 
	     "people's social activities, astounds even the most " +
	     "exclusive traveler.  Trees align the stone benches " +
	     "that cover a sidewalk which is free from cracks and " +
	     "abrasions.  An elegant stone fountain is the " +
	     "centerpiece, although no water flows through it " +
	     "today.  You note that the square is deserted, along with " +
	     "the rest of this town, even though there is a shop to "+
             "the north.  Only an occasional guard can be " +
	     "seen.\n");

    add_item(({"fountain"}), 
	     "This fountain has been made in the image of a grand warrior.  " +
	     "He stands tall, sword high in the air in one hand, and his " +
	     "hand cupped toward the sky in another.  On his cupped hand, " +
	     "you can see a light water stain, suggesting that this is " +
	     "where the water poured from.\n");

    add_item(({"trees", "sidewalk", "square"}), 
	     "A true picture of elegance.  The people of Ribos must pay " +
	     "some mighty taxes to keep this place up.\n");
   
    add_exit(RIBOS_DIR + "road3", "south", 0);
    add_exit(RIBOS_DIR + "road1", "west", 0);
    add_exit(RIBOS_DIR + "road2", "east", 0);


/*  Not sure why the shop was removed, but I'm opening it again. Lilith */
    add_exit(RIBOS_DIR + "shop", "north", 0);

    reset_room();
}

