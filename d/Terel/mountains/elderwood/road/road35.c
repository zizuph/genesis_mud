/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 
#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"
#define FIELD_DIR  MOUNTAIN_DIR + "elderwood/field/"
#define STRONGHOLD MOUNTAIN_DIR + "stronghld/"



public void
create_room()
{
    ::create_room();
    set_short("in a mountain pass");
    set_long("The road ends before a massive stone wall " +
      "which divides the pass north and south. I giant " + 
      "shining gate is set within the stone to the north.\n");
     
    add_item(({"giant gate","gate","shining gate","giant shining gate"}),
               "The shining gate appears to have been set in solid rock " +
               "which forms the massive stone wall blocking the pass.\n");

    add_item(({"massive rock wall","stone wall","wall"}),
               "The massive stone wall appears to have been made of solid " +
               "stone. The wall runs from the west to the east dividing " +
               "the pass to the north and south.\n");

    add_exit(DEFAULT    + "road34", "south");
    add_exit(STRONGHOLD + "main_gate", "north");
    add_exit(FIELD_DIR  + "field_g6", "east",0,4,1);
    add_exit(FIELD_DIR  + "field_g4", "west",0,4,1);
    add_exit(FIELD_DIR  + "field_f4", "southwest",0,4,1);
    add_exit(FIELD_DIR  + "field_f6", "southeast",0,4,1);
    reset_room();
}


