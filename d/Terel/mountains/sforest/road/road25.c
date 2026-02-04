/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "sforest/include/road";

#define DEFAULT    MOUNTAIN_DIR + "sforest/road/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The road continues " +
       "north and southeast.\n");


    add_exit(DEFAULT + "road26", "north");
    add_exit(DEFAULT + "road24", "southeast");

    reset_room();
}


