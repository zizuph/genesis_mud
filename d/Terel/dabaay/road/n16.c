/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * n16.c Road from Dabaay
 *
 * Goldberry August 9, 1999 
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

    if (jenglea_logger->query_locale("n16"))
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
    
    set_short("On the southern road, in a dark forest");
    set_long(
        "You are on the southern road, in the north end of a dark forest. "+
        "Trees, shrubs, and vines line the road to both sides. The road "+
        "bends from the north to the southeast here.\n");

    add_item(({"forest","forests"}),
        "Trees and shrubs of various species, line the road on all "+
        "sides.\n");

    add_item(({"tree","trees"}),
        "You can see several different varieties of trees. From conifers "+
        "and pines, to old oaks and cedars, the forests seem to thrive with "+
        "ancient life.\n");

    add_item(({"shrub","shrubs","bush","bushes","vine","vines"}),
        "Various evergreens and leafy vines contend for the remaining "+
        "soil among the trees.\n");

    
    add_exit(DAB_ROAD + "n17", "north", 0);
    add_exit(DAB_ROAD + "n15", "southeast", 0);
    reset_room();
}
