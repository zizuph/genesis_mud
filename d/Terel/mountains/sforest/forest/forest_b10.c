/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc5());

    add_exit(FOREST_DIR   + "forest_c10", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_b9", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_b11", "east",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c11", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_a11", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_a9", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_a10", "south",0,4, cold_fatigue);
    reset_room();
}


