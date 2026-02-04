/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";



public void
create_room()
{
    ::create_room();
    set_short_desc("south");
    set_long_desc(random(10));

    add_exit(FOREST_DIR + "forest_d5", "north",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road14", "northeast",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road13", "east",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_c3", "west",0,4,"@@exits");
    add_exit(FOREST_DIR + "road12", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_b4", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_d4", "northwest",0,4,"@@exits");
    reset_room();
}


