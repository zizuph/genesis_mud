/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square3_4
 *
 * Town square, Mid-South side
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
    set_short("In the middle of a fishing village");
    set_long(
        "You are in the middle of a small fishing village. "+
        "Directly to your west is a simple-looking shop, "+
        "with a distinct odour about it. "+
        "Out to the east, you can see a deep blue ocean. "+
        "Near by to the north and east, is what appears to "+
        "be a large bay.\n");

    add_item(({"shop","messenger shop","building"}),
        "A simple, yet stury-looking wooden building, with a "+
        "sign that proclaims it to be the local messenger shop. "+
        "You can detect a distinctly animal-like smell coming "+
        "from within.\n");

    add_item(({"sign","shop sign"}),
        "The sign has a picture of a flying gull on it, with the "+
        "shop's name painted in red beneath it:\n"+
        "Dabaay's Menagerie of Messengers.\n");

    add_item(({"smell","animal smell","distinct smell"}),
        "You can smell the odours of what must be several animals "+
        "coming from inside the messenger shop.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    add_exit(DAB_TOWN + "square3_1", "north", 0);
    add_exit(DAB_TOWN + "square4_1", "south", 0);
    add_exit(DAB_TOWN + "square3_5", "east", 0);
    add_exit(DAB_TOWN + "mesg_shop", "west", 0);
    add_exit(DAB_TOWN + "square3_2", "northeast", 0);
    add_exit(DAB_TOWN + "square4_2", "southeast", 0);
}
