/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * npier_3.c
 *
 * The boat from Emerald docks here.
 * Modified from epier_s.c
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
    set_short("At the end of a long pier");
    set_long(
        "This is a long wooden pier on the northern side of the docks. "+
        "To the north you can see where the northern part of the bay "+
        "reaches the sandy shores. The pier stretches out from the "+
        "south, where you can see the main boardwalk of the docks.\n"+
        "There is a sign here.\n");

    add_item(({"pier", "wooden pier"}), 
        "It's a well-built wooden pier. It will withstand the " +
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
    
    add_item("sign","A wooden sign nailed to the pier.\n");
    add_cmd_item("sign","read",
		 "Due to numerous acts of thievery, pickpocket\n"+
		 "and passenger harm, the routes from Dabaay have been\n"+
		 "reduced to a single line to Last in the middle north\n"+
		 "pier.\n"+
		 "\n-- Genesis ShipLines Company\n");

    add_exit(DAB_HARB + "bwalk_7", "south", 0);
}
