/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc7());

    add_exit(FOREST_DIR   + "forest_i12", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i11", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_h11", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g12", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g11", "southwest",0,4, cold_fatigue);

    reset_room();
}


