/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc3() + "A road can be seen through the trees " +
       "to the west.\n");

    add_exit(FOREST_DIR   + "forest_m11", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road22", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_k10", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_k11", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_k12", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_m12", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_m10", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_l12", "east",0,4, cold_fatigue);

    reset_room();
}


