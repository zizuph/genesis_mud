/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square2_4
 *
 * Town square, Mid-North side
 * Goldberry October 13, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"
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
    set_short("In the middle of a fishing village");
    set_long(
        "You are in the middle of a small fishing village. "+
        "Farther to the east, you can see a deep blue ocean "+
        "beyond what appears to be a "+
        "bay. Closer in, you can see several ships tied to piers. "+
        "To your west, you can see the general store of the town. "+
        "South of you is the local post office.\n");
    
    add_item(({"store","shop","general store"}),
        "The building to your west appears to be the local general "+
        "store. You can probably find something to buy there, or "+
        "perhaps sell off some of your extra items.\n");

    add_item(({"post","post office","office"}),
        "To your south stands the local post office. From there "+
        "you can see if you have any letters waiting for you. "+
        "You may also send out letter from there as well.\n");

    add_item(({"jetty","stone jetty"}),	
        "A stone extension of the village walkways, connecting to "+
        "a boardwalk in the northeast.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    
    add_exit(DAB_TOWN + "square2_2", "north", 0);
    add_exit(DAB_TOWN + "dpost", "south", 0);
    add_exit(DAB_TOWN + "square2_5", "east", 0);
    add_exit(DAB_TOWN + "dshop", "west", 0);
    add_exit(DAB_TOWN + "square2_3", "northeast", 0);
    add_exit(DAB_TOWN + "square2_1", "northwest", 0);
    add_exit(DAB_TOWN + "square3_1", "southeast", 0);
    reset_room();
}
