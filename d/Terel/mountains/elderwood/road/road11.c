/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 
#define FOREST_DIR    MOUNTAIN_DIR + "elderwood/forest/"


public void
create_room()
{
    ::create_room();
    set_short_desc("forest_road");
    set_long_desc("forest_road");


    add_exit(DEFAULT + "road12", "northeast");
    add_exit(DEFAULT + "road10", "south");
    add_exit(FOREST_DIR + "forest_a5", "east",0,1,1);
    add_exit(FOREST_DIR + "forest_a3", "west",0,1,1);
    add_exit(FOREST_DIR + "forest_b3", "northwest",0,1,1);
    add_exit(FOREST_DIR + "forest_b4", "north",0,1,1);

    reset_room();
}


