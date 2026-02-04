/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc5() + "You notice a road through the " + 
       "trees to the west and to the northwest.\n");

    add_exit(FOREST_DIR   + "forest_e8", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road14", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_d9", "east",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_e9", "northeast",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road15", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c7", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c8", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c9", "southeast",0,4, cold_fatigue);
    reset_room();
}


