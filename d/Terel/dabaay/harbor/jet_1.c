/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * jet_1.c
 *
 * Jetty, west end
 * Goldberry July 14, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_HARB DABAAY_DIR + "harbor/"
#define DAB_TOWN DABAAY_DIR + "town/"

inherit DAB_HARB + "port_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("On the west end of a stone jetty");
    set_long(
        "You are on a stone jetty, just east of the village "+
        "of Dabaay. The jetty continues out a bit farther to the "+
        "east where it meets with the end of a wooden boardwalk. "+
        "You can make out some docked ships to the east.\n");
    
    add_item(({"jetty","stone jetty"}),	
        "A stone extension of the village walkways to the west.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    
    add_exit(DAB_TOWN + "square1_4", "west", 0);
    add_exit(DAB_HARB + "jet_2", "east", 0);
}
