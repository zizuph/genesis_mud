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
       "to the west, northwest and southwest.\n");

    add_exit(FOREST_DIR   + "forest_s7", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road28", "west",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road29", "northwest",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road27", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_q7", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_q8", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_r8", "east",0,4, cold_fatigue);

    reset_room();
}


