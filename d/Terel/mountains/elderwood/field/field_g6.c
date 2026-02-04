/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";

#define STRONGHOLD MOUNTAIN_DIR + "stronghld/"

public void
create_room()
{
    ::create_room();

    set_long("The mountains rise high above " +
       "on either side of the wide pass. The sheer walls " +
       "of the pass look nearly impossible to scale. " +
       "The pass ends before a massive stone wall which " + 
       "blocks the nothern pass. Towards the northwest you see " +
       "a giant shining gate.\n");

    add_item(({"giant gate","gate","shining gate","giant shining gate"}),
               "The shining gate appears to have been set in solid rock " +
               "which forms the massive stone wall blocking the pass.\n");

    add_cmd_item(({"walls","sheer walls","mountain","pass",}),
                 ({"climb","scale"}),
                   "You are unable to climb the sheer rock face.\n");

    add_exit(FIELD_DIR  + "field_f6", "south",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road34", "southwest",0,4,"@@exits");
    add_exit(ROAD_DIR   + "road35", "west",0,4,"@@exits");
    add_exit(STRONGHOLD + "main_gate", "northwest");



    reset_room();
}


