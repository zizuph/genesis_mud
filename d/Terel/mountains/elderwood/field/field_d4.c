/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";



public void
create_room()
{
    ::create_room();

    set_long(query_long() + "The field ends before the mouth " +
       "of a large mountain pass leading further into the mountains. " +
       "A road can be seen to the northeast.\n");

    add_exit(FIELD_DIR  + "field_d5", "east",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c4", "south",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c5", "southeast",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c3", "southwest",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_d3", "west",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_e4", "north",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road33", "northeast",0,4,"@@exits");

    reset_room();
}


