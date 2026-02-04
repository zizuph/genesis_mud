/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Notorious Hand Cell Hideout
 * Tomas  -- May 2000
 */

#include "/d/Terel/include/Terel.h"

inherit MOUNTAIN_DIR + "redlair/hideout/include/hideout_base";

#define  DEFAULT   MOUNTAIN_DIR + "redlair/hideout/"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short(query_short());
    set_long(query_long() +
             "The tunnel ends here returning to the south.\n");

                
    add_exit(DEFAULT + "hideout11", "south",0,4);


    reset_room();
}