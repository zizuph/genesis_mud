/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * e_gate.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

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
        guard -> move_living("M", TO);
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
    set_short("Eastern gate");
    set_long("You are standing on the village path very close to the " +
	     "eastern fence. To the east there is a gate in the fence. " +
	     "The path continues in the western direction.\n");
    
    add_item(({"fence", "wooden fence"}), 
	     "This is the eastern part of the tall wooden fence that " +
	     "surrounds this village. It was built to protect the " +
	     "village people from the creatures in the forest north of " +
	     "here. There is a gate in the fence east from here.\n");
    
    add_item(({"gate", "wooden gate"}),
	     "The wooden gate is open.\n");
    
    add_cmd_item(({"gate", "wooden gate"}), "open",
		 "You cannot do that! The gate is already open.\n");

    add_cmd_item(({"gate", "wooden gate"}), "close",
		 "You cannot do that! The open gate is " +
		 "firmly attached to the fence with a bar.\n");

    add_item(({"bar", "wooden bar"}),
	     "The wooden bar looks very heavy and securely fastened " +
	     "to the fence and the gate.\n");

    add_cmd_item(({"bar", "wooden bar"}),
		 ({"get",   "take",  "lift",  "move"}),
		 ({"@@too_heavy","@@too_heavy","@@too_heavy", "@@too_heavy"}));

    add_exit(PORT_DIR + "beach/path", "east", 0);
    add_exit(PORT_DIR + "path5", "west", 0);

    set_alarm(1.0, -1.0, "reset_room");
}

/*
 * Function name: closed
 * Description:   vbfc for west exit.  Print a message that it is closed.
 * Returns:       1 to indicate the exit has been handled.
 */
public int
closed()
{
    write("The gate is closed and barred. You cannot go east.\n");
    return 1;
}

/*
 * Function_name: too_heavy
 * Decription:    vbfc for actions that try to get/lift/move the bar
 * Returns:       A message that the bar is too heavy.
 */
public string
too_heavy()
{
    return "The bar is too heavy!\n";
}
