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
       "to the southwest.\n");

    add_exit(FOREST_DIR   + "forest_o10", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road23", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_n9", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_m10", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_m11", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_o11", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_o9", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_n11", "east",0,4, cold_fatigue);

    reset_room();
}


