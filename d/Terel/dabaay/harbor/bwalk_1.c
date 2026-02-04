/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * bwalk_1.c
 *
 * Boardwalk, west end
 * Goldberry July 14, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_HARB DABAAY_DIR + "harbor/"

inherit DAB_HARB + "port_room";

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
        "You are on a wooden boardwalk, east of the village "+
        "of Dabaay. Wooden piers stretch out to the north and south, "+
        "while the boardwalk continues east, out into the bay. "+
        "To the west, a stone jetty leads into the village.\n");
    
    add_item(({"piers", "wooden piers"}), 
        "Well-built wooden piers. They will withstand the " +
        "worst of storms.\n");
    
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

    add_item(({"jetty","stone jetty"}), 
        "A stone walkway built up from the west shore of the bay.\n");
 
    add_exit(DAB_HARB + "npier_1", "north", 0);
    add_exit(DAB_HARB + "spier_1", "south", 0);
    add_exit(DAB_HARB + "bwalk_2", "east", 0);
    add_exit(DAB_HARB + "jet_2",   "west", 0);
}
