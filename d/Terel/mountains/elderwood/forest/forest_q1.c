/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";



public void
create_room()
{
    ::create_room();
    set_short_desc("west");
    set_long_desc(random(10));

    add_exit(FOREST_DIR + "forest_r1", "north",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_q2", "east",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_r2", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_p2", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_p1", "south",0,4,"@@exits");


    reset_room();
}


