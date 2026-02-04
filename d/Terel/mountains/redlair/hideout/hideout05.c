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
             "The tunnel continues north and southeast.\n");

                
    add_exit(DEFAULT + "hideout03", "southeast",0,4);
    add_exit(DEFAULT + "hideout06", "north",0,4);


    reset_room();
}