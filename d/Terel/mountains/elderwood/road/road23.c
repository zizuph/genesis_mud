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


    add_exit(DEFAULT + "road24", "northwest");
    add_exit(DEFAULT + "road22", "southeast");
    add_exit(FOREST_DIR + "forest_n9", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_o8", "north",0,4,1);
    add_exit(FOREST_DIR + "forest_o9", "northeast",0,4,1);
    add_exit(FOREST_DIR + "forest_n7", "west",0,4,1);
    add_exit(FOREST_DIR + "forest_m7", "southwest",0,4,1);

    reset_room();
}


