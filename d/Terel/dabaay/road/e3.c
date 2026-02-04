/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * e3.c
 * road from Dabaay
 *
 * Goldberry October 7, 1999 
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
    set_short("On a dirt path outside of a village");
    set_long(
        "You are making your way along a path that slopes down from the "+
        "west to the east. Looking to the east, you can see what appears to "+
        "be a village of sorts. On the eastern horizon, the blue line of an "+
        "ocean is visible. The path runs uphill to the west, into a "+
        "thickening forest.\n");
    
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
        "Strong hints of fish and saltwater float up from the east.\n");

    add_item(({"ocean","horizon","blue ocean","blue line"}),
        "Off in the distant east, you can make out a deep blue body of water.\n");
    
    add_exit(DAB_ROAD + "e2", "west", 0);
    add_exit(DAB_ROAD + "e4", "east", 0);
}
