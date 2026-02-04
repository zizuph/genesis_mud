/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * square2_3
 *
 * Town square, Mid-North side
 * Goldberry October 13, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"
#define  DAB_NPC DABAAY_DIR + "npc/"
#define  JENGLEA_LOC DABAAY_DIR + "obj/jenglea_loc"

inherit DAB_TOWN + "town_room";

public string*
query_moving_object_list()
{
    object jenglea_logger; 
    mixed  log_there = find_object(JENGLEA_LOC);
    if(objectp(log_there))
      jenglea_logger = find_object(JENGLEA_LOC);
    else
      jenglea_logger = clone_object(JENGLEA_LOC); 

    if (jenglea_logger->query_locale("square2_3"))
    {
        return (({DAB_NPC + "jenglea"}));
    }
}

mixed
query_loc()
{
    return find_object(JENGLEA_LOC);
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
        "Directly to your east is a large bay, with piers "+
        "extending out into it from the north.\n");
    
    add_item(({"jetty","stone jetty"}),	
        "A stone extension of the village walkways, connecting to "+
        "a boardwalk in the northeast.\n");
    
    add_item(({"ships"}),	
        "They are a bit too far away to make out any details, but "+
        "some appear to be docked along the boardwalk.\n");

    add_item(({"boardwalk","wooden boardwalk"}),
        "A wooden walkway, bustling with the activities of a fishing "+
        "port.\n");

    
    add_exit(DAB_TOWN + "square1_7", "north", 0);
    add_exit(DAB_TOWN + "square2_5", "south", 0);
    add_exit(DAB_TOWN + "square2_2", "west", 0);
    add_exit(DAB_TOWN + "square1_6", "northwest", 0);
    add_exit(DAB_TOWN + "square2_6", "southeast", 0);
    add_exit(DAB_TOWN + "square2_4", "southwest", 0);
    reset_room();
}
