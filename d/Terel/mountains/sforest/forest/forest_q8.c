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

    add_exit(FOREST_DIR   + "forest_r8", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_q7", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_r7", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_p7", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_p8", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_p9", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_q9", "east",0,4, cold_fatigue);

    reset_room();
}


