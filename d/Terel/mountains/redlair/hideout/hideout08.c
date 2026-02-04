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
             "The tunnel splits in three directions here, " +
           "north, southwest and southeast.\n");

                
    add_exit(DEFAULT + "hideout07", "southeast",0,4);
    add_exit(DEFAULT + "hideout06", "southwest",0,4);
    add_exit(DEFAULT + "hideout09", "north",0,4);


    reset_room();
}