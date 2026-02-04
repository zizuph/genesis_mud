/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
#include "/d/Terel/guilds/riders/include/guild.h"
inherit LAST_DIR + "include/nroad";

#define DEFAULT    LAST_DIR + "nroad/" 
#define RIDER_ROAD  RIDER_DIR + "room/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The main road ends before a " +
       "smaller road leading west.\n");


//    add_exit(DEFAULT + "nroad12", "north");
    add_exit(DEFAULT + "nroad11", "south");

    add_exit(RIDER_ROAD + "road01", "west");

    reset_room();
}


