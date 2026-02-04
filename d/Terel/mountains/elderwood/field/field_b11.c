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

    add_exit(FIELD_DIR  + "field_b10", "west",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_a11", "south",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_a10", "southwest",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c10", "northwest",0,4,"@@exits");

    reset_room();
}


