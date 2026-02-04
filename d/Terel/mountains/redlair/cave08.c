/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave08.c
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
             "The air here is thin as the temperature gets hotter. " +
           "The path leads deeper into the cave towards the northeast.\n");
    
    DARK;
    
    add_exit(MOUNTAIN_DIR + "redlair/cave07", "west");
    add_exit(MOUNTAIN_DIR + "redlair/cave09", "northeast");

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
    return "The walls are really hot!\n";
}

