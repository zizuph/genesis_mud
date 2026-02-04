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

    add_exit(FOREST_DIR + "forest_h6", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_f5", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_g6", "east",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_h1", "northwest",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road16", "southeast",0,4,"@@exits");

    reset_room();
}


