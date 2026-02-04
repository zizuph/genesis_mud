/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square4_5
 *
 * Town square, Southern side
 * Goldberry October 13, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"

inherit DAB_TOWN + "town_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("In the southern reaches of a fishing village");
    set_long(
        "You are in the southern area of a small fishing village. "+
        "To your east is what appears to be a large inn of sorts. "+
        "Out to the east, you can see a deep blue ocean. "+
        "Near by to the north and east, is what appears to "+
        "be a large bay.\n");
    
    add_item(({"inn","large inn"}),
        "Before you to the east, stands a well-built and warm-"+
        "looking inn. There is a sign hanging over the door.\n");

    add_item(({"sign"}),
        "The sign has a carved image of an ale tankard and reads:\n"+
        "The Stumble Inn\n");

    add_cmd_item("sign","read",
        "The sign has a carved image of an ale tankard and reads:\n"+
        "The Stumble Inn\n");
        
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    add_exit(DAB_TOWN + "stumble", "east", 0);
    add_exit(DAB_TOWN + "square4_4", "west", 0);
}
