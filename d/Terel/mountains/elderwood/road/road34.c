/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 
#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"
#define FIELD_DIR  MOUNTAIN_DIR + "elderwood/field/"


public void
create_room()
{
    ::create_room();
    set_short_desc("field_road");
    set_long("The road leads to mouth of the mountain pass. " +
       "In the distance you can just make out a massive rock " +
       "wall extending from one end to the other separating the " +
       "northern pass from the southern areas of Terel.\n");
     

    add_exit(DEFAULT    + "road33", "south");
    add_exit(DEFAULT    + "road35", "north");
    add_exit(FIELD_DIR  + "field_f6", "east",0,4,1);
    add_exit(FIELD_DIR  + "field_f4", "west",0,4,1);
    add_exit(FIELD_DIR  + "field_e4", "southwest",0,4,1);
    add_exit(FIELD_DIR  + "field_g6", "northeast",0,4,1);
    add_exit(FIELD_DIR  + "field_g4", "northwest",0,4,1);
    add_exit(FIELD_DIR  + "field_e6", "southeast",0,4,1);
    reset_room();
}


