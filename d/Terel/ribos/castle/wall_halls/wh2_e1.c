/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * wh2_e1.c
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
    add_exit(TOWER_DIR + "se_tower2",  "south",  0);
    add_exit(WALL_HALL_DIR + "wh2_e1a", "north", 0);
}
