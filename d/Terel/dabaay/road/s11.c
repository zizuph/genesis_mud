/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * s11.c
 * Road from Dabaay
 *
 * Goldberry August 23, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"
#define  DAB_NPC DABAAY_DIR + "npc/"
#define  JENGLEA_LOC DABAAY_DIR + "obj/jenglea_loc"

inherit DAB_ROAD + "road";

public string*
query_moving_object_list()
{
    object jenglea_logger;   
    mixed  log_there = find_object(JENGLEA_LOC);
    if(objectp(log_there)) 
      jenglea_logger = find_object(JENGLEA_LOC);
    else
      jenglea_logger = clone_object(JENGLEA_LOC);

    if (jenglea_logger->query_locale("s11"))
    {
        return (({DAB_NPC + "jenglea"}));
    }
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
set_short("On a dirt road in a dark forest");
    set_long(
        "You are on a dirt road that runs from the northwest to "+ 
        "the southeast. A dark and dense forest looms off to the sides "+
        "of your path. The way looks to be brighter to the southeast.\n");
 
    add_item(({"forest","forests"}),
        "Dark trees and scraggly shrubs of several varieties, line "+
        "the road on all sides.\n");
 
    add_item(({"tree","trees"}),
        "You can see several different varieties of trees. Mostly, you "+
        "spy mossy evergreens and shaggy willows.\n");
 
    add_item(({"shrub","shrubs","bush","bushes"}),
        "Various evergreens and crawling vines abide in great masses "+
        "along the forest floor.\n");
 
    add_exit(DAB_ROAD + "s10", "northwest", 0);
    add_exit(DAB_ROAD + "s12", "southeast", 0);
    reset_room();
}
