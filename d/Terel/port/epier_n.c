/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * epier_n.c
 *
 * Pier to
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
    object boat;

    ::create_room();
    set_short("Eastern pier");
    set_long("This is the eastern pier. North you see the beginning of " +
	     "a road and south the pier continues out in the sea. " +
	     "West you see a bay and beyond it you see another pier. " +
	     "There is a distinct smell in the air. " +
	     "There is a small sign here.\n");
    
    add_item("sign",
	     "It has a picture of a rising new moon over a dark forest " +
	     "on it.\n");
    
    add_item(({"pier", "wooden pier", "eastern pier"}), 
	     "It's a well-built wooden pier. It will withstand the " +
	     "worst of storms.");
    
    add_item(({"other pier", "western pier"}), 
	     "It looks similar to this pier, but it is hard to judge " +
	     "from this distance.\n");
    
    add_item(({"bay"}),	"Out on it some fishing boats have anchored.\n");
    
    add_item(({"sea"}), "It looks cold and blue.");
    
    add_item(({"road"}), 
	     "It looks well-kept and well-travelled. There are some " +
	     "houses next to it.\n");
    add_cmd_item("sign","read","Passage to Faerie.\n");

    add_exit(PORT_DIR + "road11", "north", 0);
    add_exit(PORT_DIR + "epier_mid", "south", 0);

    boat = clone_object(SHIP_DIR + "e_ship");
    boat->move(TO);

    set_alarm(5.0, -1.0, "start_boat", boat);
}

/*
 * Function name: start_boat
 * Description:   Start up the boat
 */
start_boat(object boat)
{
    
    if (boat && present(boat, TO)) {
        boat->start_ship();
    }
}
