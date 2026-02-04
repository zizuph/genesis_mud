/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc5() + "A road can be seen through the trees " +
       "to the west and north.\n");

    add_exit(ROAD_DIR     + "road19", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road18", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g9", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g10", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g8", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i10", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_h10", "east",0,4, cold_fatigue);

    reset_room();
}


