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
    set_long("You are standing at a T-crossroad. The Great Plaza street " +
	     "continues to the east and west. A minor lit street runs " +
	     "north from here. Further down the north street you are able " +
	     "to spot a huge chain, that arrives from above. Looking " +
	     "south you see a fairly big and intact building, it is the " +
	     "former Palace of Xak Tsaroth. All around you, you can see " +
	     "collapsed houses, and houses that leans on each other. A " +
	     "stream runs along the street.\n");

    add_exit(LOWER + "street21", "north");
    add_exit(LOWER + "street1", "east");
    add_exit(LOWER + "street3", "west");
}



