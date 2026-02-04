/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave14.c
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
    set_long("The path ends before a smaller cavern. Several " +       
       "pieces of thick shells lay about the debris. The " +
       "entrance to the cave is to the south\n");

    add_item(({"shell","shells","thick shell","thick shells"}),
       "Pieces of thick shells scatter about the area.\n");

    add_item(({"debris"}),"A mix of twigs, branches and bones.\n");
    
    DARK;
    
    add_exit(MOUNTAIN_DIR + "redlair/cave11", "south");

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
    return "The stench is awful here. It smells of sulphur and rotten " +
       "eggs!\n";
}
