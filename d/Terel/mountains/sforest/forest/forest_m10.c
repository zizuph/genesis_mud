/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc4() + "A road can be seen through the trees " +
       "to the west and south.\n");

    add_exit(FOREST_DIR   + "forest_n10", "north",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road23", "west",0,4, cold_fatigue);
    add_exit(ROAD_DIR     + "road22", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_l11", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_n11", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_n9", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_m12", "east",0,4, cold_fatigue);

    reset_room();
}


