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


    add_exit(DEFAULT + "road23", "northwest");
    add_exit(DEFAULT + "road21", "southeast");
    add_exit(FOREST_DIR + "forest_m10", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_n9", "north",0,4,1);
    add_exit(FOREST_DIR + "forest_n10", "northeast",0,4,1);
    add_exit(FOREST_DIR + "forest_m8", "west",0,4,1);
    add_exit(FOREST_DIR + "forest_l8", "southwest",0,4,1);

    reset_room();
}


