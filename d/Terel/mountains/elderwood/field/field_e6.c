/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";



public void
create_room()
{
    ::create_room();

    set_long("The mountains rise high above " +
       "on either side of the wide pass. The sheer walls " +
       "of the pass look nearly impossible to scale. The " +
       "pass continues onward to the north. To the south, " +
       "leads back to the fields. You notice a road to the west.\n");

    add_cmd_item(({"walls","sheer walls","mountain","pass",}),
                 ({"climb","scale"}),
                   "You are unable to climb the sheer rock face.\n");

    add_exit(FIELD_DIR  + "field_d6", "south",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road32", "southwest",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_f6", "north",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road33", "west",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road34", "northwest",0,4,"@@exits");


    reset_room();
}


