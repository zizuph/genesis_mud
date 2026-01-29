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
             "intricately inlaid tile floor. This is the southern part of " +
	     "the circular room which extends further to the north. The " +
	     "light in this room emanats from a marble statue there. " +
	     "An exit is leading south into another circular " +
	     "room, and another is leading west.\n");

    LIGHT;

    add_item(({"statue", "marble statue"}), "You can't do that from here.\n");
    add_item("floor", "It is made of finest marble.\n");

    add_exit(TEMPLE + "s_h_c", "south");
    add_exit(TEMPLE + "s_w_r", "west");
    add_exit(TEMPLE + "chamber2", "north");
}






