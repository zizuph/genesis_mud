/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Town square, Northern side
 * Goldberry October 13, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"
#define DAB_ROAD DABAAY_DIR + "road/"
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
        "You are at the edge of a small fishing village. The village "+
        "opens up more to the east, while to the west, you can see a "+
        "dirt road leading away from the town. A white-washed building "+
        "stands to the south of you. Farther to the east, you can see "+
        "a deep blue ocean beyond what appears to be a bay. Closer in, "+
        "you can see several ships tied to piers.\n");
    
    add_item(({"building","white building","white-washed building"}),
        "A two-story building with a look of importance about it. "+
        "The front of the building appears to be to the southeast.\n");

    add_item(({"road","dirt road"}),
        "A simple path of dirt, leading west into a forest.\n");

    add_item("forest",
        "A dense forest lies to the west of the village.\n");

    add_item(({"jetty","stone jetty"}),	
        "A stone extension of the village walkways, connecting to a "+
        "wooden boardwalk.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    
    add_exit(DAB_TOWN + "square1_2", "east", 0);
    add_exit(DAB_ROAD + "e4", "west", 0);
    reset_room();
}
