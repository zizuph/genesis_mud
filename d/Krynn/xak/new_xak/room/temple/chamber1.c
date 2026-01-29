/* 
 * Xak Tsaroth - Temple of Mishakal
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{    
    set_short("In the Chamber of Mishakal");
    set_long("You are standing under a vast dome that rise high above an " +
             "intricately inlaid tile floor. This is the northern part of " +
	     "the circular room which extends further to the south. An exit " +
	     "is leading north into another circular room, and another " +
	     "is leading west. The light in this room emanates from a marble " +
	     "statue to the south.\n");

    LIGHT;

    add_item(({"statue", "marble statue"}), "You can't do that from here.\n");
    add_item("floor", "It is made of finest marble.\n");

    add_exit(TEMPLE + "n_h_c", "north");
    add_exit(TEMPLE + "n_w_r", "west");
    add_exit(TEMPLE + "chamber2", "south");
}






