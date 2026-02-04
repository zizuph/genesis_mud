/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc1() + "The road can be seen through the trees " +
       "to the southwest.\n");

    add_exit(FOREST_DIR   + "forest_p9", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_o8", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_n9", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_n10", "southeast",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road24", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_p10", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_p8", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_o10", "east",0,4, cold_fatigue);

    reset_room();
}


