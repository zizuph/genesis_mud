/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit LAST_DIR + "include/nroad";

#define DEFAULT    LAST_DIR + "nroad/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The road continues " +
       "northeast and south.\n");


    add_exit(DEFAULT + "nroad08", "northeast");
    add_exit(DEFAULT + "nroad06", "south");

    reset_room();
}


