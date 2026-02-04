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


    add_exit(DEFAULT + "road20", "north");
    add_exit(DEFAULT + "road18", "south");
    add_exit(FOREST_DIR + "forest_h9", "southeast",0,4,1);
    add_exit(FOREST_DIR + "forest_i10", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_i7", "west",0,4,1);
    add_exit(FOREST_DIR + "forest_j7", "northwest",0,4,1);
    add_exit(FOREST_DIR + "forest_h7", "southwest",0,4,1);


    reset_room();
}


