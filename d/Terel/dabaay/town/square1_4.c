/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Town square, Northern side
 * Goldberry October 13, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"
#define DAB_HARB DABAAY_DIR + "harbor/"
#define DAB_NPC  DABAAY_DIR + "npc/"

inherit DAB_TOWN + "town_room";

public string*
query_moving_object_list()
{
    return ({DAB_NPC + "tguard1",
             DAB_NPC + "tguard1"});
}

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
        "You are in the northern reaches of a small fishing village. "+
        "A jetty stretches out to the east, leading to the bay's "+
        "piers. Several ships can be seen swinging at anchor.\n");
    
    add_item(({"jetty","stone jetty"}),	
        "A stone extension of the village walkways, connecting to a "+
        "wooden boardwalk.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    
    add_exit(DAB_TOWN + "square1_7", "south", 0);
    add_exit(DAB_HARB + "jet_1", "east", 0);
    add_exit(DAB_TOWN + "square1_3", "west", 0);
    add_exit(DAB_TOWN + "square1_6", "southwest", 0);
    reset_room();
}
