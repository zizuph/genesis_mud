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

    add_exit(FOREST_DIR + "forest_a3", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_c3", "north",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_c4", "northeast",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road11", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_b4", "east",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_a2", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_c2", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_b2", "west",0,4,"@@exits");

    reset_room();
}


