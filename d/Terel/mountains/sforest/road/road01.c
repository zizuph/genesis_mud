/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "sforest/include/road";

#define DEFAULT    MOUNTAIN_DIR + "sforest/road/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The road continues " +
       "northwest and southwest.\n");


    add_exit(DEFAULT + "road02", "northeast");
//  add_exit(/d/Terel/sorgum/tomb/hill_mid",0,1);
    add_exit("w/tomas/workroom", "southwest");

    reset_room();
}


