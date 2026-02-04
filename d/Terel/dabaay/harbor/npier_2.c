/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * npier_1.c
 *
 * Pier to Faerie
 * Modified from epier_n.c
 * Goldberry July 14, 1999
 * Modified - Damaris@Genesis 10/2006
 *            commented out boat to Faerie as this old area has closed.
 */

#include "/d/Terel/include/Terel.h"
#define DAB_HARB DABAAY_DIR + "harbor/"

inherit DAB_HARB + "port_room";
inherit "/d/Genesis/gsl_ships/lib/pier";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
//    object boat;

    ::create_room();
    set_short("At the end of a short pier");
    set_long(
        "This is a wooden pier on the northwestern side of the docks. "+
        "To the north you can see where the northern part of the bay "+
        "reaches the sandy shores. The pier stretches out from the "+
        "south, where you can see the main boardwalk of the docks.\n");
    
    add_item(({"pier", "wooden pier"}), 
        "It's a well-built wooden pier. It will withstand the " +
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
    
    add_cmd_item("sign",({"read","look","examine"}),
		 "Cabotage to Last.\n");

    add_exit(DAB_HARB + "bwalk_4", "south", 0);
    add_pier_entry(MASTER_OB(TO), "Dabaay", "Cabotage to Last");
    initialize_pier();

}

