/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";



public void
create_room()
{
    ::create_room();
    set_short_desc("middle");
    set_long_desc(random(10));

    add_exit(ROAD_DIR   + "road23", "north",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road22", "east",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road23", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_l9", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_l8", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_m7", "west",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_l7", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_m7", "northwest",0,4,"@@exits");

    reset_room();
}


