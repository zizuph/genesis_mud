/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * e1.c
 * road from Dabaay
 *
 * Goldberry October 7, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"
#define  JENGLEA_LOC DABAAY_DIR + "obj/jenglea_loc"
#define  DAB_NPC DABAAY_DIR + "npc/"

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

    if (jenglea_logger->query_locale("e1"))
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
    set_short("On a gently sloping path");
    set_long(
        "You are making your way along a path that slopes down from the "+
        "northwest to the southeast. The surrounding forest seems to be "+
        "thicker to the west of you. An ocean breeze can be sensed blowing "+
        "from the east.\n");
    
    add_item(({"forest","forests"}),
        "Trees and shrubs of various species, line the road on all "+
        "sides.\n");

    add_item(({"tree","trees"}),
        "You can see several different varieties of trees. From conifers "+
        "and pines, to old oaks and cedars, the forests seem to thrive with "+
        "ancient life.\n");

    add_item(({"shrub","shrubs","bush","bushes"}),
        "Various evergreens and leafy vines contend for the remaining "+
        "soil among the trees.\n");

    add_item(({"breeze","ocean breeze"}),
        "Strong hints of fish and saltwater float up from the east.\n");

    
    add_exit(DAB_ROAD + "center", "northwest", 0);
    add_exit(DAB_ROAD + "e2", "southeast", 0);
    reset_room();
}
