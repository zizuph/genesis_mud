/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * wh1_s1.c
 *
 * Vader
 * Recoded by Sorgum 950708
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
    add_exit(TOWER_DIR + "sw_tower1",  "west",  0);
    add_exit(WALL_HALL_DIR + "wh1_s1a", "east", 0);
}
