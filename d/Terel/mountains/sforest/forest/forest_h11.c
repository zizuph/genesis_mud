/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/sforest/include/local.h"

inherit MOUNTAIN_DIR + "sforest/include/forest";



public void
create_room()
{
    ::create_room();
    set_long(forest_desc6());

    add_exit(FOREST_DIR   + "forest_i11", "north",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i10", "northwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_h10", "west",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g11", "south",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g12", "southeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_g10", "southwest",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_i12", "northeast",0,4, cold_fatigue);
    add_exit(FOREST_DIR   + "forest_h12", "east",0,4, cold_fatigue);

    reset_room();
}


