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

    add_exit(FOREST_DIR + "forest_f2", "north",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_e3", "east",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_d2", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_d3", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_d1", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_f1", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_e1", "west",0,4,"@@exits");

    reset_room();
}


