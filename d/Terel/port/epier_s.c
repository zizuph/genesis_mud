/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * epier_s.c
 *
 * Eastern pier.  The boat from Emerald docks here.
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
    set_long("This is the end of the eastern pier. Some distance to " +
	     "the north you see the beginning of a road. " +
	     "To the south is nothing but the sea. " +
	     "West you see a bay and beyond it you see another pier. " +
          "There is a sign here.\n");
    
    add_item(({"pier", "wooden pier", "eastern pier"}), 
	     "It's a well-built wooden pier. It will withstand the " +
	     "worst of storms.\n");

    add_item(({"other pier", "western pier"}), 
	     "It looks similar to this pier, but it is hard to judge " +
	     "from this distance.\n");
    
    add_item(({"bay"}), "Out on it some fishing boats have anchored.\n");
    
    add_item(({"sea"}), 
	     "It looks cold and blue and covers the whole southern " +
	     "horizon.\n");
    add_item("sign","A wooden sign nailed to the pier.\n");
    add_cmd_item("sign","read","Ship to Emerald docks here.\n");

    add_exit(PORT_DIR + "epier_mid", "north", 0);
}
