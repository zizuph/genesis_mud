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

    add_exit(FOREST_DIR   + "forest_j12", "north",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_i11", "west",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_j11", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_h11", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_h12", "south",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_j13", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_i13", "east",0,4,"@@exits");

    reset_room();
}


