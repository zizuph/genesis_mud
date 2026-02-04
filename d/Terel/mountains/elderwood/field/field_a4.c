/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";



public void
create_room()
{
    ::create_room();

    set_long(query_long() + "A road can be seen to the east.\n");

    add_exit(FIELD_DIR  + "field_a5", "east",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b4", "north",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b5", "northeast",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b3", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s4", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s5", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s3", "southwest",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_a3", "west",0,4,"@@exits");
    reset_room();
}


