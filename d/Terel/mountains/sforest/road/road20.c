/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "sforest/include/road";

#define DEFAULT    MOUNTAIN_DIR + "sforest/road/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The road continues " +
       "northeast and south.\n");


    add_exit(DEFAULT + "road21", "northeast");
    add_exit(DEFAULT + "road19", "south");

    reset_room();
}


