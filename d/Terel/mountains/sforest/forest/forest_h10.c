/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc6() + "The road can be seen through the " +
       "trees to the northwest.\n");

    add_exit(FOREST_DIR   + "forest_i10", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road19", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_h9", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g10", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g11", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g9", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i11", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_h11", "east",0,4, cold_fatigue);

    reset_room();
}


