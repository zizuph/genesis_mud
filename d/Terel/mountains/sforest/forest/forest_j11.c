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

    add_exit(FOREST_DIR   + "forest_k11", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_j10", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_k10", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i10", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i11", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i12", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_k12", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_j12", "east",0,4, cold_fatigue);

    reset_room();
}


