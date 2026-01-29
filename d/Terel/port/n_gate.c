/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * n_gate.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

/*
 * Function name: reset_room
 * Description:   clone the guard if necessary
 */
public void
reset_room()
{
    object guard;
    if (!present("guard")) {
	guard = clone_object(PORT_DIR + "monster/guard");
	guard -> move_living("arrives", TO);
    }
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Outside northern gate");
    set_long("You are standing on the road to the enchanted forest. " +
	     "The road continues in the northern direction. " +
	     "A tall wooden fence is going in the east-west direction. " +
	     "Immediately to the southeast there is a tall wooden gate " +
	     "in the fence.\n");
    
    add_item(({"forest", "enchanted forest"}),
	     "The forest is great and it covers the whole northern " +
	     "horizon. Some remnants of it still exist around " +
	     "the road, although here most of it has been cut down " +
	     "by the local people.\n");

    add_item(({"gate", "wooden gate"}), "The wooden gate is open.\n");
    add_item(({"fence", "wooden fence"}), 
	     "The wooden fence is too high for you to climb. You " +
	     "better use the gate.\n");
    
    add_cmd_item(({"fence", "wooden fence"}), "climb",
		 "The wooden fence is still too high to climb!\n");

    add_exit(PORT_DIR + "road2", "north",     0);
    add_exit(PORT_DIR + "road3", "southeast", 0);

    set_alarm(1.0, -1.0, "reset_room");
}

