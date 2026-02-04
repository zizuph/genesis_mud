/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";



public void
create_room()
{
    ::create_room();

    set_long(query_long() + ".\n");

    add_exit(FIELD_DIR  + "field_a3", "east",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b2", "north",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b3", "northeast",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b1", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s2", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s3", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s1", "southwest",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_a1", "west",0,4,"@@exits");
    reset_room();
}


