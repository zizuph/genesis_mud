/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * wh4_n1.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit WALL_HALL_DIR + "top_wall_hall";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(WALL_HALL_DIR + "wh4_n1", "west", 0);
    add_exit(WALL_HALL_DIR + "wh4_n8a", "east", 0);
}
