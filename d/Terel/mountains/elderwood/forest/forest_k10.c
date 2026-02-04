/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";



public void
create_room()
{
    ::create_room();
    set_short_desc("east");
    set_long_desc(random(10));

    add_exit(ROAD_DIR     + "road21", "north",0,4,"@@exits");
    add_exit(ROAD_DIR     + "road20", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_j10", "south",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_j11", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_l11", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_k11", "east",0,4,"@@exits");

    reset_room();
}


