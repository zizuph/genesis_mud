/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_short_desc(2);
    set_long_desc(1);
    
    add_exit(FOREST_DIR   + "forest_j10", "north",0,4,1);
    add_exit(ROAD_DIR     + "road19", "west",0,4,1);
    add_exit(ROAD_DIR     + "road20", "northwest",0,4,1);
    add_exit(FOREST_DIR   + "forest_h9", "southwest",0,4,1);
    add_exit(FOREST_DIR   + "forest_h10", "south",0,4,1);
    add_exit(FOREST_DIR   + "forest_h11", "southeast",0,4,1);
    add_exit(FOREST_DIR   + "forest_j11", "northeast",0,4,1);
    add_exit(FOREST_DIR   + "forest_i11", "east",0,4,1);

    reset_room();
}


