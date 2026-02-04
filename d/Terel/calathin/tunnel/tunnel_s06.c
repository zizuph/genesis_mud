/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel_01.c
 * Calathin Escape Tunnel
 * Tomas  -- July 2000
 */

#include "/d/Terel/include/Terel.h"

inherit CALATHIN_DIR + "tunnel/tunnel_base";

#define  DEFAULT   CALATHIN_DIR + "tunnel/"


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short(query_short());
    set_long("You are standing under a stone bridge. The river streams "+
            "rather fast and some chunks of ice are passing swiftly by. "+
            "A tunnel seems to have been incorporated into the building "+
            "of this bridge.\n");

    DARK;
    
    add_exit(DEFAULT + "tunnel_s05", "north");
    add_exit(CALATHIN_DIR + "roads/road_s02", "up");



    reset_room();
}





