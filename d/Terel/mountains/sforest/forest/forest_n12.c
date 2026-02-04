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

    add_exit(FOREST_DIR   + "forest_o12", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_m11", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_n11", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_m12", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_o11", "northwest",0,4, cold_fatigue);

    reset_room();
}


