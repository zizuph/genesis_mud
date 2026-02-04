/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * bwalk_2.c
 *
 * Boardwalk, west end
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
    set_short("On the west end of the boardwalk");
    set_long(
        "You are on a wooden boardwalk, just east of the village "+
        "of Dabaay. The boardwalk continues east out into the "+
        "bay, and west back into the village.\n");

    add_item(({"bay"}),	
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east and past some other "+
        "piers, the bay opens into the sea. From this distance, you "+
        "can barely make out what appears to be a stone wall "+
        "stretching from the north shore into the bay.\n");
    
    add_item(({"sea"}), "It looks cold and blue.\n");

    add_item(({"wall","stone wall"}), 
        "It is difficult to make out any details from this distance. "+
        "Every few moments a wave crashes over the wall.\n");
    
    add_exit(DAB_HARB + "bwalk_3", "east", 0);
    add_exit(DAB_HARB + "bwalk_1", "west", 0);
    reset_room();
}
