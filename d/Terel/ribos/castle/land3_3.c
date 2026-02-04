/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * land3_3.c
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
    add_exit(CASTLE_DIR + "land3_2", "west", 0);
}
