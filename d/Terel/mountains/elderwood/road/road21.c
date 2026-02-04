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


    add_exit(DEFAULT + "road22", "northwest");
    add_exit(DEFAULT + "road20", "southwest");
    add_exit(FOREST_DIR + "forest_l11", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_k10", "south",0,4,1);
    add_exit(FOREST_DIR + "forest_k11", "southeast",0,4,1);
    add_exit(FOREST_DIR + "forest_m11", "northeast",0,4,1);
    add_exit(FOREST_DIR + "forest_m10", "north",0,4,1);
    add_exit(FOREST_DIR + "forest_l9", "west",0,4,1);


    reset_room();
}


