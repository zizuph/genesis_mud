/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * s13.c
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

    if (jenglea_logger->query_locale("s13"))
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
    set_short("At the end of a road in a dense forest");
    set_long(
        "You have reached the end of a dirt road in a dense forest. "+
        "From the frest tree-stumps and wood-chips, it looks as "+
        "though there is still work being done on extending the road "+
        "further south. The road leads back to the north.\n");
    
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

    add_item(({"stumps","tree-stumps","tree stumps"}),
        "There are several stumps of various trees, scattered amond the "+
        "trees at the south end of the road. They look to be freshly cut.\n");

    add_item(({"chips","wood-chips","wood chips"}),
        "The fresh and aromatic remnants of recent tree-fellings.\n");
    
    add_exit(DAB_ROAD + "s12", "north", 0);
    reset_room();
}
