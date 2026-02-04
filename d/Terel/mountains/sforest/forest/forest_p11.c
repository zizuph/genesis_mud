/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc4());

    add_exit(FOREST_DIR   + "forest_q11", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_p10", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_o10", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_o12", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_q10", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_o11", "south",0,4, cold_fatigue);

    reset_room();
}


