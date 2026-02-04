/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc2() + "An open field can be seen to the " +
       "north. The road is to the west and southwest.\n");

    add_exit(ROAD_DIR     + "road29", "west",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road28", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_r7", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_r8", "southeast",0,4, cold_fatigue);

    reset_room();
}


