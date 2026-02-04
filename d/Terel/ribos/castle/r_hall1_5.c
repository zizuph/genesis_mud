/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * r_hall1_5.c
 *
 * Vader
 * Recoded by Sorgum 950708
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
    set_long(query_long() + "It continues southeast and west.\n");

    add_exit(CASTLE_DIR + "r_hall1_4", "southeast", 0);
    add_exit(CASTLE_DIR + "r_hall1_6", "west",      0);
    add_exit(CASTLE_DIR + "k_bath",    "northeast", 0);

    clone_object(DOOR_DIR + "knight5_in")->move(TO);        
}
