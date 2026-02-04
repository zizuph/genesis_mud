/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc2());

    add_exit(FOREST_DIR   + "forest_e11", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_d10", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_d12", "east",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_e12", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_e10", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c10", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c11", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_c12", "southeast",0,4, cold_fatigue);
    reset_room();
}


