/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 


public void
create_room()
{
    ::create_room();
    set_short_desc("road");
    set_long("The pass opens wide revealing the " +
       "vast forest of Elderwood. The snowy road continues " +
       "onward through the forest to the north. To the " +
       "south is the southern pass entrance.\n");


    add_exit(DEFAULT + "road11", "north");
    add_exit(DEFAULT + "road09", "south");

    reset_room();
}


