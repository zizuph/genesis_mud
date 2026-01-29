/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * hotel2.c
 *
 * A hotel room.
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "hotel_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(PORT_DIR + "hotel",  "south", 0);
}

