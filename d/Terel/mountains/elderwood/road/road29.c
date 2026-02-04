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



    add_exit(DEFAULT    + "road30", "north");
    add_exit(DEFAULT    + "road28", "south");
    add_exit(FIELD_DIR  + "field_a7", "east",0,4,1);
    add_exit(FIELD_DIR  + "field_b7", "northeast",0,4,1);
    add_exit(FOREST_DIR + "forest_s8", "southeast",0,4,1);
    add_exit(FIELD_DIR  + "field_a5", "west",0,4,1);
    add_exit(FIELD_DIR + "field_b5", "northwest",0,4,1);
    add_exit(FOREST_DIR + "forest_s5", "southwest",0,4,1);

    reset_room();
}


