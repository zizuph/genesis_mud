/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * path3.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Village path");
    set_long("You are standing on a muddy village path. The path " +
	     "continues in the southeast and west directions. There are " +
	     "houses around the path. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"house", "houses"}),
	     "The houses surrounding the path are all made of timber " +
	     "from the forest north of the village.\n");

    add_exit(PORT_DIR + "path4", "west",      0);
    add_exit(PORT_DIR + "path2", "southeast", 0);
}
