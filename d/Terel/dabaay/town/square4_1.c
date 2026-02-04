/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square4_1
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
        "To your south stands a small, thatch-roof shack. "+
        "Out to the east, you can see a deep blue ocean. "+
        "Near by to the north and east, is what appears to "+
        "be a large bay.\n");
    
    add_item(({"shack","thatch-roof shach","small shack"}),
        "The purpose of the small shack does not seem to readily "+
        "evident. There aren't any signs posted on it, yet it "+
        "seems open and inviting.\n");

    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    add_exit(DAB_TOWN + "square3_4", "north", 0);
    add_exit(DAB_TOWN + "herb_shop", "south", 0);
    add_exit(DAB_TOWN + "square4_2", "east", 0);
    add_exit(DAB_TOWN + "square3_5", "northeast", 0);
}
