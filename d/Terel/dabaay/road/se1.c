/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * se1.c Path off of north road from Dabaay
 *
 * Goldberry October 7, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"
#define DAB_NPC DABAAY_DIR + "npc/"

inherit DAB_ROAD + "se_path";

public string*
query_moving_object_list()
{
    return ({DAB_NPC + "roam_half",});
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("On a small path off of the main road");
    set_long(
        "You are on a small dirt track to the southeast of the main "+
        "road. The trees here vie with masses of brush and undergrowth "+
        "for a take of the forest floor. The track branches to the south "+
        "and southeast.\n");
    
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
    
    add_exit(DAB_ROAD + "s3", "northwest", 0);
    add_exit(DAB_ROAD + "se2", "south", 0);
    add_exit(DAB_ROAD + "se3", "southeast", 0);
    reset_room();
}
