/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall3_2.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "hall_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "It continues north and south.\n");
    add_exit(CASTLE_DIR + "l_hall3_3", "north", 0);
    add_exit(CASTLE_DIR + "l_hall3_1", "south", 0);    
}
