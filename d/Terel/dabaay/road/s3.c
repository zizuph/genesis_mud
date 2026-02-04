/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * s3.c
 * Road from Dabaay
 *
 * Goldberry August 23, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"
#define DAB_NPC DABAAY_DIR + "npc/"

inherit DAB_ROAD + "road";

public string*
query_moving_object_list()
{
    return ({DAB_NPC + "roam_half"});
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("On a dirt road through a forest");
    set_long(
        "You are on a tree-lined dirt road that comes from the north "+
        "and ends here. A small track leads off into the forest to "+
        "southeast. A variety of trees and shrubs line the road on the "+
        "sides, but the path itself is free and clear of any vegetation.\n");

/*    set_long(
        "You are on a tree-lined dirt road that bends from the north "+ 
        "to the southwest. A small track leads off into the forest to "+
        "southeast. A variety of trees and shrubs line the road on the "+
        "sides, but the path itself is free and clear of any vegetation.\n");
*/
    
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

    add_item(({"track","small track"}),
        "A narrow trail cutting into the trees to the southest.\n");
    
    add_exit(DAB_ROAD + "s2", "north", 0);
//    add_exit(DAB_ROAD + "s4", "southwest", 0);
    add_exit(DAB_ROAD + "se1", "southeast", 0);
    reset_room();
}
