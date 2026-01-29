/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * path4.c
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
	     "continues in the east and west directions. There is " +
	     "a wooden fence to the west. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"fence", "wooden fence"}), 
	     "This is the western part of the tall wooden fence that " +
	     "surrounds this village. It was built to protect the " +
	     "village people from the creatures in the forest north of " +
	     "here. There is a gate in the fence west from here.\n");
    
    add_item(({"gate"}),
	     "It looks as if the gate is closed, but you must go " +
	     "closer to be sure of that.\n");

    add_exit(PORT_DIR + "w_gate", "west", 0);
    add_exit(PORT_DIR + "path3",  "east", 0);
}
