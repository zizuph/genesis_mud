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
             "The path decends deeper into the shaft towards the northeast. " +
           "You notice something strange about the wall to the southwest.\n");

    add_item(({"southwest wall","wall"}),"The wall appears to shift and shimmer " +
           "slightly as if it was transparent.\n");

    DARK;
    
    add_exit(DEFAULT + "shaft02", "northeast");
    add_exit(MOUNTAIN_DIR   + "redlair/cave03", "southwest","@@check",0,4);

    add_tell("the southwest wall shimmers slightly.\n");
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


