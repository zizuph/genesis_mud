/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square1_6
 *
 * Town square, Northern side
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
    set_short("In the north section of a fishing village");
    set_long(
        "You are in the northwestern area of a small fishing village. "+
        "The town opens up more to the south and east. "+ 
        "Farther to the east, you can see "+
        "a deep blue ocean beyond what appears to be a bay. Closer in, "+
        "you can see several ships tied to piers.\n");
    
    add_item(({"jetty","stone jetty"}),	
        "A stone extension of the village walkways, connecting to a "+
        "wooden boardwalk.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    
    add_exit(DAB_TOWN + "square1_3", "north", 0);
    add_exit(DAB_TOWN + "square2_2", "south", 0);
    add_exit(DAB_TOWN + "square1_7", "east", 0);
    add_exit(DAB_TOWN + "square1_5", "west", 0);
    add_exit(DAB_TOWN + "square1_4", "northeast", 0);
    add_exit(DAB_TOWN + "square1_2", "northwest", 0);
    add_exit(DAB_TOWN + "square2_3", "southeast", 0);
    add_exit(DAB_TOWN + "square2_1", "southwest", 0);
}
