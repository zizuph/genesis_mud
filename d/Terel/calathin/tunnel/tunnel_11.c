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
    set_long(query_long() +
             "The path decends deeper into the shaft towards the east " +
           "and to the west.\n");



    DARK;
    
    add_exit(DEFAULT + "tunnel_11a", "east");
    add_exit(DEFAULT + "tunnel_10", "west");



    reset_room();
}





