/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ne_tower0.c
 *
 * Northeast tower in the basement of the castle
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit TOWER_DIR + "lower_tower_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(WALL_HALL_DIR + "wh0_7", "southwest", 0);
    add_exit(TOWER_DIR + "ne_tower1", "up",        0);
   
}
