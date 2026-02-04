/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * s1.c
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
    set_short("On a dirt road");
    set_long(
        "You are on a tree-lined dirt road. Trees and shrubs encroach on "+ 
        "both sides of the road, but the path itself is free of "+
        "vegetation. To the north, you can see an intersection of some "+
        "sort. To the southwest, the road continues deeper into the forest.\n");
    
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

    
    add_exit(DAB_ROAD + "center", "north", 0);
    add_exit(DAB_ROAD + "s2", "southwest", 0);
}
