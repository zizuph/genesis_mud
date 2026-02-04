/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";



public void
create_room()
{
    ::create_room();

    set_long(query_long() + "A road leading southwards " +
       "into the forest can be seen to the southwest.\n");

    add_exit(FIELD_DIR  + "field_a8", "east",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b7", "north",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_b8", "northeast",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road30", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_s7", "south",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_s8", "southeast",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road28", "southwest",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road29", "west",0,4,"@@exits");

    reset_room();
}


