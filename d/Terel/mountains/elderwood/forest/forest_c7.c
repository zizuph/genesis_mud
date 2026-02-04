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

    add_exit(ROAD_DIR     + "road14", "north",0,4,"@@exits");
    add_exit(ROAD_DIR     + "road13", "west",0,4,"@@exits");
    add_exit(ROAD_DIR     + "road14", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_c8", "east",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_d8", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_b6", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_b7", "south",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_b8", "southeast",0,4,"@@exits");
    reset_room();
}


