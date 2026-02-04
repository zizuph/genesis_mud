/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square3_5
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
        "Out to the east, you can see a deep blue ocean. "+
        "Near by to the north and east, is what appears to "+
        "be a large bay.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    add_exit(DAB_TOWN + "square3_2", "north", 0);
    add_exit(DAB_TOWN + "square4_2", "south", 0);
    add_exit(DAB_TOWN + "square3_6", "east", 0);
    add_exit(DAB_TOWN + "square3_4", "west", 0);
    add_exit(DAB_TOWN + "square3_3", "northeast", 0);
    add_exit(DAB_TOWN + "square3_1", "northwest", 0);
    add_exit(DAB_TOWN + "square4_3", "southeast", 0);
    add_exit(DAB_TOWN + "square4_1", "southwest", 0);
}
