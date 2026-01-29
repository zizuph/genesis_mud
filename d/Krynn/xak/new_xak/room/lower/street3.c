/* 
 * Xak Tsaroth - Lower level
 * Originally coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{
    set_short("On the Great Plaza street");
    set_long("You are standing on the Great Plaza street. The street " +
	     "makes a turn here, heading south and east. A building " +
	     "to the north seems to have been repaired by someone " +
	     "lately. A stream of water follows the street.\n");

    add_item("building", "The building seems freshly repaired. Who " +
	     "would want to repair building down here?\n");

    add_item(({"stream", "water"}), "The water is from Newsea above you " +
	     "and it is filled with filth and dust.\n");

    add_exit(LOWER + "street2", "east");
    add_exit(LOWER + "street4", "south");
}



