/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "sforest/include/road";

#define DEFAULT    MOUNTAIN_DIR + "sforest/road/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The road continues " +
       "north and southwest.\n");


    add_exit(DEFAULT + "road03", "north");
//  add_exit(/d/Terel/sorgum/tomb/hill_mid",0,1);    
    add_exit(DEFAULT + "road01", "southwest");

    reset_room();
}


