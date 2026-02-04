/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * se4.c Path off of north road from Dabaay
 *
 * Goldberry October 7, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"

inherit DAB_ROAD + "se_path";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("At the end of a small path off of the main road");
    set_long(
        "You are at the end of a small dirt track deep in the forest. "+
        "The trail ends at the bases of a thick stand of trees. Brush and "+
        "undergrowth carpet the remaining forest floor. The track leads "+
        "back to the north.\n");
    
    add_item(({"forest","forests"}),
        "Trees, shrubs, vines, and small plants of various species, "+
        "cover all of the ground to the sides of the path.\n");

    add_item(({"tree","trees"}),
        "You can see several different varieties of trees. From conifers "+
        "and pines, to old oaks and cedars, the forests seem to thrive with "+
        "ancient life.\n");

    add_item(({"shrub","shrubs","bush","bushes"}),
        "Various evergreens and leafy vines contend for the remaining "+
        "soil among the trees.\n");

    add_item(({"brush","foliage","undergrowth"}),
        "Clumps and thickets of various plants and vines sprawl out over "+
        "the forest floor. Heady aromas float up from the foliage.\n");
    
    add_exit(DAB_ROAD + "se2", "north", 0);
}
