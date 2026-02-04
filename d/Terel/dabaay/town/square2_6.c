/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square2_6
 *
 * Town square, Mid-North side
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
        "Directly to your east is a large bay, with piers "+
        "extending out into it from the north.\n");
    
    add_item(({"jetty","stone jetty"}),	
        "A stone extension of the village walkways, connecting to "+
        "a boardwalk in the northeast.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    
    add_exit(DAB_TOWN + "square3_2", "south", 0);
    add_exit(DAB_TOWN + "square2_5", "west", 0);
    add_exit(DAB_TOWN + "square2_3", "northwest", 0);
    add_exit(DAB_TOWN + "square3_3", "southeast", 0);
    add_exit(DAB_TOWN + "square3_1", "southwest", 0);
}
