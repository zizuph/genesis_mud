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

    add_exit(ROAD_DIR   + "road30", "west",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b8", "east",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c7", "north",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c8", "northeast",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_a7", "south",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_a8", "southeast",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road29", "southwest",0,4,"@@exits");
    add_exit(ROAD_DIR  + "road31", "northwest",0,4,"@@exits");

    reset_room();
}


