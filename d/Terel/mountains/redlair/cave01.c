/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave01.c
 *
 * Red Dragon Lair
 * Tomas  -- Dec. 1999
 */

#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "redlair/cave_room";


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() +
             "The path decends deeper into the cave towards the east. " +
           "To the west you can see the exit leading outside.\n");
    
    DARK;
    
    add_exit(MOUNTAIN_DIR + "redlair/cave02", "east");
    add_exit(SILVER_DIR   + "forest_qz/forest_r25", "west","@@check");

    reset_room();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "You sense a slight scent of sulphur.\n";
}


public string
touch_desc()
{
    return "The walls are cool here.\n";
}


check()
{
   if(TP->query_prop("_terel_hatchling")) 
   {
      write("stay boy, STAY!\n");
      return 1;
   }
   return 0;
}


