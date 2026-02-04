/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";



public void
create_room()
{
    ::create_room();
    set_short_desc("middle");
    set_long_desc(random(10));

    add_exit(FOREST_DIR   + "forest_q9", "north",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_p8", "west",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_o8", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_o10", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_q10", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_q8", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_p10", "east",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_o9", "south",0,4,"@@exits");

    reset_room();
}


