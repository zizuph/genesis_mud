/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit LAST_DIR + "include/nroad";

#define DEFAULT    LAST_DIR + "nroad/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The road continues " +
       "north and south. The south leads back to the " +
       "town of Last. \n");


    add_exit(DEFAULT + "nroad06", "north");
    add_exit(DEFAULT + "nroad04", "south");

    reset_room();
}


