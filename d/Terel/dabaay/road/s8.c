/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * s8.c
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
    set_short("On a dirt road in a dark forest");
    set_long(
        "You are on a dirt road that curves from the northwest to "+ 
        "the south. A dark and dense forest looms off to the sides "+
        "of your path.\n");
    
    add_item(({"forest","forests"}),
        "Dark trees and scraggly shrubs of several varieties, line "+ 
        "the road on all sides.\n");

    add_item(({"tree","trees"}),
        "You can see several different varieties of trees. Mostly, you "+
        "spy mossy evergreens and shaggy willows.\n");

    add_item(({"shrub","shrubs","bush","bushes"}),
        "Various evergreens and crawling vines abide in great masses "+
        "along the forest floor.\n");

    
    add_exit(DAB_ROAD + "s7", "northwest", 0);
    add_exit(DAB_ROAD + "s9", "south", 0);
}
