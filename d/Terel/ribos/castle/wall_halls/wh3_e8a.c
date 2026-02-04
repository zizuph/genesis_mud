/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * wh3_e8.c
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
    add_exit(WALL_HALL_DIR + "wh3_e8", "north", 0);
    add_exit(WALL_HALL_DIR + "wh3_e1a", "south", 0);
}
