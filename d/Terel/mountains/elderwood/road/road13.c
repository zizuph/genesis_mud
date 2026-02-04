/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 
#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"


public void
create_room()
{
    ::create_room();
    set_short_desc("forest_road");
    set_long_desc("forest_road");


    add_exit(DEFAULT + "road14", "north");
    add_exit(DEFAULT + "road12", "southwest");
    add_exit(FOREST_DIR + "forest_b6", "south",0,4,1);
    add_exit(FOREST_DIR + "forest_b7", "southeast",0,4,1);
    add_exit(FOREST_DIR + "forest_c7", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_c5", "west",0,4,1);
    add_exit(FOREST_DIR + "forest_d5", "northwest",0,4,1);

    reset_room();
}


