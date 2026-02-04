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

    add_exit(DEFAULT    + "road32", "southeast");
    add_exit(DEFAULT    + "road34", "north");
    add_exit(FIELD_DIR  + "field_d5", "south",0,4,1);
    add_exit(FIELD_DIR  + "field_e6", "east",0,4,1);
    add_exit(FIELD_DIR  + "field_e4", "west",0,4,1);
    add_exit(FIELD_DIR  + "field_d4", "southwest",0,4,1);
    add_exit(FIELD_DIR  + "field_f6", "northeast",0,4,1);
    add_exit(FIELD_DIR  + "field_f4", "northwest",0,4,1);
    reset_room();
}


