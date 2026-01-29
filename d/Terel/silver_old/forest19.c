/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest19.c
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
    add_exit(FOREST_EXIT,             "north", 0);
    add_exit(SILVER_DIR + "forest14", "south", 0);
    add_exit(SILVER_DIR + "forest18", "west",  0);
    add_exit(FOREST_EXIT,             "east",  0);
}
