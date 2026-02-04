/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * n17.c Road from Dabaay
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
    set_short("On the southern road");
    set_long(
        "You are on the southern road, south of a vast and mysterious "+
        "forest. To the south, the road enters a more normal looking, "+
        "yet darker, forest.\n");
    
    add_item(({"mysterious forest"}),
        "The forest to the north seems to have a mysterious air about it. "+
        "This must be the enchanted forest that you have heard tell of.\n");

    add_item(({"forest","forests","dark forest","darker forest"}),
        "Trees and shrubs of various species, line the road on all "+
        "sides.\n");

    add_item(({"tree","trees"}),
        "You can see several different varieties of trees. From conifers "+
        "and pines, to old oaks and cedars, the forests seem to thrive with "+
        "ancient life.\n");

    add_item(({"shrub","shrubs","bush","bushes"}),
        "Various evergreens and leafy vines contend for the remaining "+
        "soil among the trees.\n");

    
    add_exit(ENCHANT_DIR + "road_s12", "north", 0);
    add_exit(DAB_ROAD + "n16", "south", 0);
}
