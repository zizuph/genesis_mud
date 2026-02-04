/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc1() + "You notice a road " +
       "past the trees to the west and to the northwest.\n");

    add_exit(ROAD_DIR   + "road12", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_a6", "east",0,4, cold_fatigue);
    add_exit(ROAD_DIR   + "road11", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_b6", "northeast",0,4, cold_fatigue);
    reset_room();
}


