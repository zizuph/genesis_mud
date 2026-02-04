/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc3());

    add_exit(FOREST_DIR   + "forest_d10", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c9", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c11", "east",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_d11", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_d9", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_b9", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_b10", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_b11", "southeast",0,4, cold_fatigue);
    reset_room();
}


