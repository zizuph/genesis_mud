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

    add_exit(FOREST_DIR   + "forest_r7", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_s7", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_q7", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_q8", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_q9", "southeast",0,4, cold_fatigue);

    reset_room();
}


