/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square3_2
 *
 * Town square, Mid-South side
 * Goldberry October 13, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"
#define DAB_NPC DABAAY_DIR + "npc/"

inherit DAB_TOWN + "town_room";

public string*
query_moving_object_list()
{
    return ({DAB_NPC + "roam_half",
             DAB_NPC + "roam_half"});
}

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

    add_exit(DAB_TOWN + "square2_6", "north", 0);
    add_exit(DAB_TOWN + "square3_5", "south", 0);
    add_exit(DAB_TOWN + "square3_3", "east", 0);
    add_exit(DAB_TOWN + "square3_1", "west", 0);
    add_exit(DAB_TOWN + "square2_5", "northwest", 0);
    add_exit(DAB_TOWN + "square3_6", "southeast", 0);
    add_exit(DAB_TOWN + "square3_4", "southwest", 0);
    reset_room();
}
