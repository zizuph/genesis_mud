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
    set_long("The street makes a turn here and heads off to the " +
	     "north and west. To the west you can see a open area amonge " +
	     "the rubble. The stream continues to follow the street.\n");

    add_exit(LOWER + "street3", "north");
    add_exit(LOWER + "plaza", "west");
}



