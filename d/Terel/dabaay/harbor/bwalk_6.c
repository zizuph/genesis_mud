/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * bwalk_6.c
 *
 * Boardwalk, middle 
 * Goldberry July 14, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define DAB_HARB DABAAY_DIR + "harbor/"
#define  DAB_NPC DABAAY_DIR + "npc/"
#define  JENGLEA_LOC DABAAY_DIR + "obj/jenglea_loc"

inherit DAB_HARB + "port_room";

public string*
query_moving_object_list()
{
    object jenglea_logger; 
    mixed  log_there = find_object(JENGLEA_LOC);
    if(objectp(log_there))
      jenglea_logger = find_object(JENGLEA_LOC);
    else
      jenglea_logger = clone_object(JENGLEA_LOC); 

    if (jenglea_logger->query_locale("bwalk_6"))
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
    set_short("On the boardwalk");
    set_long(
        "You are on a wooden boardwalk, just east of the village "+
        "of Dabaay. The boardwalk continues east out into the "+
        "bay, and west back into the village.\n");
    
    add_item(({"bay"}),	
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east and past some other "+
        "piers, the bay opens into the sea. There is a stone wall "+
        "stretching from the north shore into the bay.\n");
    
    add_item(({"sea"}), "It looks cold and blue.\n");

    add_item(({"wall","stone wall"}), 
        "The wall appears to be made from large stones, piled up "+
        "in a line from the north point to the center of the bay's "+
        "entrance. Every few moments a wave crashes over the wall.\n");
    
    add_exit(DAB_HARB + "bwalk_7", "east", 0);
    add_exit(DAB_HARB + "bwalk_5", "west", 0);
    reset_room();
}
