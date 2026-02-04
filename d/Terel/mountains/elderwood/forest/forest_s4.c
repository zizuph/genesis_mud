/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";



public void
create_room()
{
    ::create_room();
    set_short_desc("north");
    set_long_desc(random(10));

    add_exit(FIELD_DIR  + "field_a4", "north",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s5", "east",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_a5", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_r5", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_r4", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s3", "west",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_r3", "southwest",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_a3", "northwest",0,4,"@@exits");


    reset_room();
}


