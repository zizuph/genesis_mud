/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave15.c
 *
 * An empty room in the cave.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The caves continue deeper into the rock.\n");

    DARK;

    add_exit(ORC_CAVE_DIR + "cave14","west");
    add_exit(ORC_CAVE_DIR + "cave13","southeast");
}
