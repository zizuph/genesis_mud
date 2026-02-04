/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Notorious Hand Cell Hideout
 * Tomas  -- May 2000
 */

#include "/d/Terel/include/Terel.h"

inherit MOUNTAIN_DIR + "redlair/hideout/include/shaft_base";

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
             "You notice dim light up ahead as the shaft continues north.\n"); 

    add_tell("You hear the sounds of rushing water to the north.\n");

    DARK;
    
    add_exit(DEFAULT + "cavern01", "north");
    add_exit(DEFAULT + "shaft11", "southwest");


    reset_room();
}


check()
{
   if(TP->query_prop("_terel_is_hand")) 
   {
      write("stay boy, STAY!\n");
      return 1;
   }
   return 0;
}


