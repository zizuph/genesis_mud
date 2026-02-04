/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * n13.c Road from Dabaay
 *
 * Goldberry August 9, 1999 
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
    
    set_short("On a dirt road, in the midst of a dark forest");
    set_long(
        "You are traveling a dirt road that runs through a dark forest of trees, "+
        "vines, and shrubs. The road runs from the west to the east here.\n");

    add_item(({"forest","forests"}),
        "Trees and shrubs of various species, line the road on all "+
        "sides.\n");

    add_item(({"tree","trees"}),
        "You can see several different varieties of trees. From conifers "+
        "and pines, to old oaks and cedars, the forests seem to thrive with "+
        "ancient life.\n");

    add_item(({"shrub","shrubs","bush","bushes","vines","vine"}),
        "Various evergreens and leafy vines contend for the remaining "+
        "soil among the trees.\n");

    
    add_exit(DAB_ROAD + "n14", "west", 0);
    add_exit(DAB_ROAD + "n12", "east", 0);
}
