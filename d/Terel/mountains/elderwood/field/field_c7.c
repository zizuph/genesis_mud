/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";



public void
create_room()
{
    ::create_room();

    set_long(query_long() + "You see a road to the west.\n");

    add_exit(FIELD_DIR  + "field_c8", "east",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b7", "south",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b8", "southeast",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_d8", "north",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road31", "west",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road30", "southwest",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road32", "northwest",0,4,"@@exits");

    reset_room();
}


