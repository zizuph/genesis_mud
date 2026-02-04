/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * land2_2.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "landing_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(CASTLE_DIR + "land2_3", "east", 0);
    add_exit(CASTLE_DIR + "land2_1", "west", 0);
}
