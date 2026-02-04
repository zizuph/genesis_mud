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


    add_exit(DEFAULT + "road26", "north");
    add_exit(DEFAULT + "road24", "southeast");
    add_exit(FOREST_DIR + "forest_p7", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_q7", "northeast",0,4,1);
    add_exit(FOREST_DIR + "forest_p5", "west",0,4,1);
    add_exit(FOREST_DIR + "forest_q5", "northwest",0,4,1);
    add_exit(FOREST_DIR + "forest_o5", "southwest",0,4,1);

    reset_room();
}


