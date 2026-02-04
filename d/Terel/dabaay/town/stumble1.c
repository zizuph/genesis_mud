/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * stumble1.c
 *
 * A hotel room.
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"

inherit DAB_TOWN + "stumble_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(DAB_TOWN + "stumble",  "southeast", 0);
}
