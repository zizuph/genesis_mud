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
    set_long_desc("field_road");

    add_exit(DEFAULT    + "road31", "south");
    add_exit(DEFAULT    + "road33", "northwest");
    add_exit(FIELD_DIR  + "field_d7", "east",0,4,1);
    add_exit(FIELD_DIR  + "field_c7", "southeast",0,4,1);
    add_exit(FIELD_DIR  + "field_d5", "west",0,4,1);
    add_exit(FIELD_DIR  + "field_c5", "southwest",0,4,1);
    add_exit(FIELD_DIR  + "field_e6", "north",0,4,1);

    reset_room();
}


