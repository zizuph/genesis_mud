/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel_s02.c
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
             "There is a very faint feeling of air moving from the south.\n");

    DARK;
    
    add_exit(DEFAULT + "tunnel_s03", "south");
    add_exit(DEFAULT + "tunnel_01", "north");



    reset_room();
}





