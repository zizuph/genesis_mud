/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * hotel3.c
 *
 * A hotel room.
 */

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR + "hotel_room";


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LAST_DIR + "whdragon",  "southwest", 0);
}

