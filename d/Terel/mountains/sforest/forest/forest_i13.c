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

    add_exit(FOREST_DIR   + "forest_j13", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i12", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_j12", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_h12", "southwest",0,4, cold_fatigue);


    reset_room();
}


