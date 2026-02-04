/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * r_hall1_1.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "hall_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long("This is a large, regal hallway.  It is decorated by " +
	     "paintings and busts of great people.  It continues " +
	     "north, and ends in a balcony to the south.  " +
          "\n");

    add_exit(CASTLE_DIR + "king_balc", "south", "@@closed"); 
    add_exit(CASTLE_DIR + "r_hall1_2",  "north", 0);

    clone_object(DOOR_DIR + "knight1_in")->move(TO);    
}

/*
 * Function name: closed
 * Description:   Don't let player pass for now.
 * Returns:       1
 */
public int
closed()
{
    write("The balcony is under construction.  Please return later.\n");
    return 1;
}
