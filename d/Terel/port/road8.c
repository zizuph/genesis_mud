/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road8.c
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
    set_short("Village road");
    set_long("You are standing at the southern end of the Village road. " +
	     "The road goes north from here. South you can walk out on a " +
	     "wooden pier. There is a house to the west which has a " +
	     "sign on the wall next to the door. To the east you see a " +
	     "bay, and on the other side of it you see another pier going " +
	     "out into the sea. There is a distinct smell in the air.\n"); 
    
    add_item(({"pier", "wooden pier"}),
	     "It is a sturdy wooden pier. The people who built it " +
	     "certainly did know how to do it. It looks as if it will " +
	     "withstand even the worst of storms.\n");
    
    add_item(({"eastern pier", "other pier"}),
	     "It looks similar to the pier south of here, but from " +
	     "this distance it is hard to judge.\n");
    
    add_item(({"bay"}), "Out on it you see some fishing boats anchored.\n");
    
    add_item(({"sea"}),
	     "It looks cold and blue, and looking to the south you see " +
	     "not a trace of land, only a few struggling sailing boats.\n");
    
    add_item("sign", "@@sign_info");
    add_cmd_item("sign", "read", "@@sign_info");

    add_exit(PORT_DIR + "road7",   "north", 0);
    add_exit(PORT_DIR + "wpier_n", "south", 0);
    add_exit(PORT_DIR + "shop",    "west",  0);
}

/*
 * Function name: sign info
 * Description:   vbfc for the sign
 * Returns:       what is written on the sign
 */
public string
sign_info()
{
    return "The sign says: Fisherman's Shop\n";
}
