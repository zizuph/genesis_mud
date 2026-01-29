/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest20.c
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
    add_exit(FOREST_EXIT, "north", 0);
    add_exit(FOREST_EXIT, "south", 0);
    add_exit(FOREST_EXIT, "west",  0);

}
