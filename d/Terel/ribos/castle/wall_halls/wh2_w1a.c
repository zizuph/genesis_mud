/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * wh2_w1.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit WALL_HALL_DIR + "wall_hall";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(WALL_HALL_DIR + "wh2_w1", "south", 0);
    add_exit(WALL_HALL_DIR + "wh2_w8a", "north", 0);
}
