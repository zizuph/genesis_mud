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

    add_exit(FOREST_DIR   + "forest_i11", "north",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_i10", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_h10", "west",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_g11", "south",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_g12", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_g10", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_i12", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_h12", "east",0,4,"@@exits");

    reset_room();
}


