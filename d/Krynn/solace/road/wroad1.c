/* created by Aridor, 08/14/94 */

#include "local.h"

inherit SOLACE_ROOM

void
create_solace_room()
{
    set_short("Road in a valley");
    set_long("You are on the road to or from Gateway. Here, the road " +
	     "runs along the west side of a merry stream, leading " + 
	     "north towards some kind of fork in the road and " +
	     "disappearing further down the valley to the south. " +
	     "Along both sides of the road and stream, hills rise up " +
	     "which are covered with bushes and a few trees. Further " +
	     "northwest, higher mountains are visible.\n");
    add_exit(HROAD + "xroad","north",0,2);
    add_exit(HROAD + "wroad2","south",0,2);
    add_item(({"stream","rocks","streambed","bed","water"}),
	     "It is quite a broad stream, but you wouldn't call it a " +
	     "river just yet. Rocks in the streambed let the water bubble " +
	     "excitedly before it rushes off to the south.\n");
    add_item("mountains",
	     "The mountains in the northwest are quite high and barren, " +
	     "and they are not very far away.\n");
    add_item("road",
	     "It's a gravel road leading north and south.\n");
    add_item(({"trees","bushes"}),
	     "There are many bushes covering the hills around you, " +
	     "and an occasional beech tree is scattered about.\n");
}

