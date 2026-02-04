/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc3()+ "You notice a road through " +
       "trees leading west and north.\n");

    add_exit(ROAD_DIR   + "road13", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR   + "road12", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_b7", "east",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_c7", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_a7", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_a5", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR + "forest_a6", "south",0,4, cold_fatigue);
    reset_room();
}


