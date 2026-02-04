/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "sforest/include/road";

#define DEFAULT    MOUNTAIN_DIR + "sforest/road/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + " Up ahead, you notice " +
       "a mountainrange just above the trees. The " +
       "road continues north and south.\n");

    add_item(({"mountains","mountainrange"}),
       "The jagged tips of a vast mountainrange " +
       "can be seen above the trees.\n");

    add_exit(DEFAULT + "road27", "north");
    add_exit(DEFAULT + "road25", "south");

    reset_room();
}


