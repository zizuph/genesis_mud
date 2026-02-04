/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 


public void
create_room()
{
    ::create_room();
    set_short_desc("road");
    set_long_desc("road");


    add_exit(DEFAULT + "road04", "north");
    add_exit(DEFAULT + "road02", "south");

    reset_room();
}


