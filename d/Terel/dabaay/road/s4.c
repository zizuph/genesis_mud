/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * s4.c
 * Road from Dabaay
 *
 * Goldberry August 23, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"

inherit DAB_ROAD + "road";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("On a dirt road in a dense forest");
    set_long(
        "You are on a tree-lined dirt road that runs from the northeast "+ 
        "to the southwest. A variety of trees and shrubs line the road on the "+
        "sides, but the path itself is free and clear of any vegetation.\n");

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

    
    add_exit(DAB_ROAD + "s3", "northeast", 0);
    add_exit(DAB_ROAD + "s5", "southwest", 0);
}
