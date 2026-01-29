/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road3.c
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
    set_short("Inside gate");
    set_long("You are standing just southeast of a wooden gate. " +
	     "A tall fence goes in the east-west direction. " +
	     "To the south you see a small fishing village, and " +
	     "beyond it you see the sea. " +
	     "The road goes northwest, to the gate, and to the south " +
	     "it branches to the southeast and southwest. There is " +
	     "a sign here.\n");

    add_item("gate", "It's a sturdy wooden gate, it's open.\n");
    add_item("fence", "It's a tall wooden fence.\n");
    add_item("village", "The village lies on both sides of a river.  " +
	     "The river is south and east from here.\n");

    add_item("sign", "@@sign_info");
    add_cmd_item("sign", "read", "@@sign_info");

    add_exit(PORT_DIR + "n_gate", "northwest", 0);
    add_exit(PORT_DIR + "road4",  "southwest", 0);
    add_exit(PORT_DIR + "bridge", "southeast", 0);
}

/*
 * Function name: sign_info
 * Description:   vbfc for the sign
 * Returns:       what is written on the sign
 */
public string
sign_info()
{
    return
     "The sign reads:\n" +
     "   Northwest:    Enchanted forest, and garden, and Town of Calathin\n" +
     "   Southwest:    West Pier\n" +
     "   Southeast:    East Pier and beach\n";
}
