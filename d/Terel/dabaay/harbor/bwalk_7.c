/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * bwalk_7.c
 *
 * Boardwalk, east end
 * Goldberry July 14, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_HARB DABAAY_DIR + "harbor/"
#define DAB_NPC DABAAY_DIR + "npc/"

inherit DAB_HARB + "port_room";

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
    set_short("On the boardwalk");
    set_long(
        "You are on a wooden boardwalk, east of the village "+
        "of Dabaay. Wooden piers stretch out to the north and south, "+
        "while the boardwalk continues back to the west.\n");
    
    add_item(({"piers", "wooden piers"}), 
        "Well-built wooden piers. They will withstand the " +
        "worst of storms.\n");
    
    add_item(({"bay"}),
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east, the bay opens into "+
        "the sea. There is a stone wall stretching from the north "+
        "shore into the bay.\n");
 
    add_item(({"sea"}), "It looks cold and blue.\n");
 
    add_item(({"wall","stone wall"}),
        "The wall is made up of large gray stones, piled up "+
        "in a line from the north point to the center of the bay's "+
        "entrance. You can see watercraft traversing the calm waters "+
        "created by this artificial cove. Every few moments a wave "+
        "crashes over the wall.\n");
 
    add_exit(DAB_HARB + "npier_3", "north", 0);
    add_exit(DAB_HARB + "spier_3", "south", 0);
    add_exit(DAB_HARB + "bwalk_6", "west", 0);
    reset_room();
}
