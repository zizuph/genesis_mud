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
             "The tunnel splits to the northwest, northeast " +
           "and to the south.\n");

                
    add_exit(DEFAULT + "hideout02", "south",0,4);
    add_exit(DEFAULT + "hideout04", "northeast",0,4);
    add_exit(DEFAULT + "hideout05", "northwest",0,4);


    reset_room();
}