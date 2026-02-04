/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * n7.c Road from Dabaay
 *
 * Goldberry August 9, 1999 
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
    set_short("On a dirt road, deep in the forest");
    set_long(
        "You are on a dirt road that cuts through a dense forest. Trees "+
        "and shrubs grow in abundance on the sides of the road while the "+
        "path remains clear. There is a small path to the northeast. "+
        "The road bends from the northwest to the south here.\n");

    
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

    
    add_exit(DAB_ROAD + "n8", "northwest", 0);
    add_exit(DAB_ROAD + "ne1", "northeast", 0);
    add_exit(DAB_ROAD + "n6", "south", 0);
    reset_room();
}
