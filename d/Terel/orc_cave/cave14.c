/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave14.c
 *
 * An empty room in the cave.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() +
	     "The stones in the cave are black and slippery.  " +
	     "You sense the presence of danger nearby.\n");

    add_item(({"stones", "stone"}), "The stones are made of ordinary rock.\n");

    DARK;
    
    add_exit(ORC_CAVE_DIR + "cave15", "east");
    add_exit(ORC_CAVE_DIR + "cave03", "south");
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "There is a smell of foul creatures in the air.\n";
}
