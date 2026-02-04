/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * ne1.c Path off of north road from Dabaay
 *
 * Goldberry August 9, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"

inherit DAB_ROAD + "ne_path";

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
        "You are on a small dirt track deep in a dense forest. "+
        "The trees and shrubs are thick and abundant here, and the "+
        "smells are strong, and pleasant. The path ends here with "+
        "the only progressable way to the southeast.\n");
    
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

    add_item(({"plants","small plants"}),
        "Strong and healthy plants line the edges of the path. Spicy aromas "+
        "drift off of the large variety of small plants.\n");
    
    add_exit(DAB_ROAD + "ne1", "southeast", 0);
}
