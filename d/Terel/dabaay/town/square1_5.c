/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square1_5
 *
 * Town square, Northern side
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
    set_short("In the north section of a fishing village");
    set_long(
        "You are at the western edge of a small fishing village. "+
        "Directly to your west, is an important looking white-washed "+
        "building. The town opens up more to the south and east. "+ 
        "Farther to the east, you can see "+
        "a deep blue ocean beyond what appears to be a bay. Closer in, "+
        "you can see several ships tied to piers.\n");

    add_item(({"building","white building","white-washed building"}),
        "A tall building made of rough-sawn planks, and painted with "+
        "a white-wash. This appears to be the town-hall.\n");
    
    add_item(({"jetty","stone jetty"}),	
        "A stone extension of the village walkways, connecting to a "+
        "wooden boardwalk.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    add_exit(DAB_TOWN + "square1_2", "north", 0);
    add_exit(DAB_TOWN + "square2_1", "south", 0);
    add_exit(DAB_TOWN + "square1_6", "east", 0);
    add_exit(DAB_TOWN + "thall", "west", 0);
    add_exit(DAB_TOWN + "square1_3", "northeast", 0);
    add_exit(DAB_TOWN + "square2_2", "southeast", 0);
    reset_room();
}
