/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit LAST_DIR + "include/nroad";

#define DEFAULT    LAST_DIR + "nroad/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The road continues " +
       "north and southwest.\n");


    add_exit(DEFAULT + "nroad11", "north");
    add_exit(DEFAULT + "nroad09", "southwest");

    reset_room();
}


