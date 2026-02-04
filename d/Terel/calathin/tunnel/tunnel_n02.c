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
             "The tunnel has a slight grade, rising gently to the west and "+
             "flowing deeper to the east.\n");

    DARK;
    
    add_exit(DEFAULT + "tunnel_n03", "east");
    add_exit(DEFAULT + "tunnel_n01", "west");



    reset_room();
}





