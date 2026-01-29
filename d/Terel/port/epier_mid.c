/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * epier_mid.c
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
    set_short("Eastern pier");
    set_long("This is the middle of the eastern pier. " +
	     "There is a distinct smell in the air. " +
	     "There is a small sign here.\n");
    
    add_item("sign","A wooden sign nailed to the pier.\n");
    add_cmd_item("sign","read","Passage to the town of Last.\n");
    
    add_item(({"pier", "wooden pier", "eastern pier"}), 
	     "It's a well-built wooden pier. It will withstand the " +
	     "worst of storms.\n");
    
    add_item(({"other pier", "western pier"}), 
	     "It looks similar to this pier, but it is hard to judge " +
	     "from this distance.\n");

    
    add_item(({"bay"}), "Out on it some fishing boats have anchored.\n");

    
    add_item(({"sea"}), "It looks cold and blue.\n");

    add_exit(PORT_DIR + "epier_n", "north", 0);
    add_exit(PORT_DIR + "epier_s", "south", 0);
}
