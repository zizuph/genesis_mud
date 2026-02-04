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


    add_exit(DEFAULT + "road13", "northeast");
    add_exit(DEFAULT + "road11", "southwest");
    add_exit(FOREST_DIR + "forest_b6", "east",0,1,1);
    add_exit(FOREST_DIR + "forest_a6", "southeast",0,1,1);
    add_exit(FOREST_DIR + "forest_a5", "south",0,1,1);
    add_exit(FOREST_DIR + "forest_b4", "west",0,1,1);
    add_exit(FOREST_DIR + "forest_c4", "northwest",0,1,1);


    reset_room();
}


