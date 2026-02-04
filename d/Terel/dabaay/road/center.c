/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * center.c
 *
 * Center intersection of Dabaay roads 
 * Goldberry August 9, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"
#define DAB_NPC DABAAY_DIR + "npc/"

inherit DAB_ROAD + "road";

public string*
query_moving_object_list()
{
    return ({DAB_NPC + "roam_half",
             DAB_NPC + "roam_half"});
}



/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A fork in the road");
    set_long(
        "You are standing at a fork in the road. The forest seems "+
        "to be denser along the roads to the north and south. The "+
        "path to the southeast appears to be on a gentle downslope. "+
        "You can detect a a faint ocean breeze coming from the east.\n");
    
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
        "A faint, yet discernible hint of saltwater and fish.\n");
    
    add_exit(DAB_ROAD + "n1", "north", 0);
    add_exit(DAB_ROAD + "e1", "southeast", 0);
    add_exit(DAB_ROAD + "s1", "south", 0);
    reset_room();
}
