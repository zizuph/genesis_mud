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
             "The path decends deeper into the cave towards the southeast.\n");
    
    DARK;
    
    add_exit(MOUNTAIN_DIR + "redlair/cave01", "west");
    add_exit(MOUNTAIN_DIR + "redlair/cave03", "southeast");

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
    return "A faint trace of sulphur in the air.\n";
}


public string
touch_desc()
{
    return "The walls are cool and smooth to the touch.\n";
}

