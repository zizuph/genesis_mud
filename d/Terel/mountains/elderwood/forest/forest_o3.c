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

    add_exit(FOREST_DIR + "forest_p3", "north",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_o4", "east",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_p4", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_n4", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_n3", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_o2", "west",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_n2", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_p2", "northwest",0,4,"@@exits");

    reset_room();
}


