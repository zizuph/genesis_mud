/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave12.c
 *
 * A cave room that is home to two wolves.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ORC_CAVE_DIR + "monster/wolf",
            ORC_CAVE_DIR + "monster/wolf"});

}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() +
	     "The eastern tunnel is damp and hot.  " +
	     "Small fireflies behind a glass window emit a calm, " +
	     "yellow light.\n");

    add_item("fireflies",
	     "You stop to look at the dazzling dance of the fireflies.\n");
    
    add_item(({"window", "glass", "glass window"}),
	     "It is securely embedded in the wall.\n");

    add_exit(ORC_CAVE_DIR + "cave07", "west");
    add_exit(ORC_CAVE_DIR + "cave08", "northwest");
    add_exit(ORC_CAVE_DIR + "cave11", "east");
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
    return "It smells kind of like a dog who has been playing in a sulfur " +
	"andbox.\n";
}
