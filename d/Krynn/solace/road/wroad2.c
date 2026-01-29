/* created by Aridor, 08/14/94 */

#include "local.h"

inherit SOLACE_ROOM

void
create_solace_room()
{
    set_short("Road in a valley");
    set_long("You are on the road to or from Gateway. Here, the road " +
	     "runs along the west side of a small river, disappearing " +
	     "north up the valley and continuing downwards to the southeast " +
	     "next to the river. Along both sides of the road and river, " +
	     "hills rise up which are covered with bushes and a few trees.\n");
    add_exit(HROAD + "wroad1","north",0,2);
    add_exit(HROAD + "wroad3","southeast",0,2);
    add_item(({"river","water"}),
	     "This is a small river and the since it is quite steep and narrow " +
	     "here in the valley, it is raging noisily and water is spraying " +
	     "everywhere.\n");
    add_item("hill",
	     "The hills along the road and river are not very high, and they " +
	     "are covered with bushes and a few trees.\n");
    add_item(({"road","gravel"}),
	     "It's a gravel road leading north and south.\n");
    add_item(({"trees","bushes"}),
	     "There are many bushes covering the hills around you, " +
	     "and an occasional beech tree is scattered about.\n");
}

