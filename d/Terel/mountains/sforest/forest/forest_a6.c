/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc1() + "You notice the road " +
       "beyond the trees to the northwest.\n");

    add_exit(FOREST_DIR + "forest_b6", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_a7", "east",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_a5", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_b7", "northeast",0,4, cold_fatigue);
    add_exit(ROAD_DIR + "road12", "northwest",0,4, cold_fatigue);
    reset_room();
}


