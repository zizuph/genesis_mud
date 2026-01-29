/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * w_gate.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Western gate");
    set_long("You are standing on the village path very close to the " +
	     "western fence. To the west there is a gate in the fence. " +
	     "The path continues in the eastern direction.\n");
    
    add_item(({"fence", "wooden fence"}), 
	     "This is the western part of the tall wooden fence that " +
	     "surrounds this village. It was built to protect the " +
	     "village people from the creatures in the forest north of " +
	     "here. There is a gate in the fence west from here.\n");
    
    add_item(({"gate", "wooden gate"}), "The wooden gate is closed and " +
	     "barred.\n");
    
    add_cmd_item(({"gate", "wooden gate"}), "open", 
		 "You cannot do that! The gate has been barred.\n");
    
    add_item(({"bar", "wooden bar"}),
	     "The wooden bar looks very heavy and securely fastened " +
	     "to the fence and the gate.\n");
    
    add_cmd_item(({"bar", "wooden bar"}),
		 ({"get",   "take",  "lift",  "move"}),
		 ({"@@too_heavy","@@too_heavy","@@too_heavy", "@@too_heavy"}));

    add_exit(PORT_DIR + "path4", "east", 0);
}

/*

   else
   write("Welcome to Alvarad Gabriel!\n");
   return 0;
 * Function name: closed
 * Description:   vbfc for west exit.  Print a message that it is closed.
 * Returns:       1 to indicate the exit has been handled.
 */
public int
closed()
{
   write("You run into the closed and barred gate. Ouch!\n");
   say("Einstein runs into the closed and barred gate.\n");
   if (this_player()->query_name() != "Gabriel")
   {
   return 1;
   }

   else
   {
   return 0;
   }
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
