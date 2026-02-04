/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc2() + "A road can be seen through the trees " +
       "to the west, southwest and northwest.\n");

    add_exit(ROAD_DIR     + "road22", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road21", "west",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road20", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_j10", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_j11", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_l11", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_k11", "east",0,4, cold_fatigue);

    reset_room();
}


