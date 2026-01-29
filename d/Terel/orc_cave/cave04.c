/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave04.c
 *
 * A cave room near the entrance.
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
    set_long(query_long() + "The tunnel splits into two exits here.\n");

    DARK;

    add_exit(ORC_CAVE_DIR + "entrance", "northwest");
    add_exit(ORC_CAVE_DIR + "cave05",   "east");
}

