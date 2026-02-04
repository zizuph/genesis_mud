/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave07.c
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
             "As you decend deeper in the tunnel the temperature seems to rise. " +
           "The path leads deeper into the cave towards the east.\n");
    
    DARK;
    
    add_exit(MOUNTAIN_DIR + "redlair/cave06", "west");
    add_exit(MOUNTAIN_DIR + "redlair/cave08", "east");

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
    return "It smells like a sulfur furnace from hell in here!\n";
}



public string
touch_desc()
{
    return "The walls feel hot!\n";
}

