/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";



public void
create_room()
{
    ::create_room();

    set_long(query_long() + "You see a road to the east.\n");

    add_exit(ROAD_DIR   + "road31", "east",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road32", "northeast",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b5", "south",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road30", "southeast",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_d5", "north",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c4", "west",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b4", "southwest",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_d4", "northwest",0,4,"@@exits");

    reset_room();
}


