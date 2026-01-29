/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest23.c
 *
 * A room in the silver forest.
 */

#include "/d/Terel/include/Terel.h"
inherit SILVER_DIR + "forest_room";

#include "local.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "To the north, you see a Cornerstone.\n");

    add_exit("/d/Terel/common/road/forest_edge", "north", 0);
    add_exit(SILVER_DIR + "forest18", "south", 0);
    add_exit(FOREST_EXIT,             "west",  0);
    add_exit(FOREST_EXIT,             "east",  0);
}
