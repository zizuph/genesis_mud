/* created by Aridor, 09/29/94 */

#include "local.h"

inherit SOLACE_ROOM

void
create_solace_room()
{
    set_short("Road in a valley");
    set_long("You are on the road between Crystalmir Lake and Gateway. " +
	     "Here, the road runs along the west side of a small river, " +
	     "disappearing northwest up the valley and continuing " +
	     "downwards to the southeast where you can see smoke rising up " +
	     "into the sky! Along both sides of the road and river, " +
	     "hills rise up which are covered with bushes and a few trees.\n");
    add_exit(HROAD + "wroad2","northwest",0,2);
    add_exit(HROAD + "gateway","southeast",0,2);
    add_item(({"river","water"}),
	     "This is a small river and the since it is quite steep and " +
	     "narrow here in the valley, it is raging noisily and water is " +
	     "spraying everywhere.\n");
    add_item("hill",
	     "The hills along the road and river are not very high, and " +
	     "they are covered with bushes and a few trees.\n");
    add_item(({"road","gravel"}),
	     "It's a gravel road leading north and south.\n");
    add_item(({"trees","bushes"}),
	     "There are many bushes covering the hills around you, " +
	     "and an occasional beech tree is scattered about.\n");
    add_item(({"smoke","trail of smoke","trail"}),
	     "These are several thin trails of smoke rising up into the sky " +
	     "in the southeast. By going southeast you are likely to reach " +
	     "their sources.\n");
    add_item(({"sky"}),
	     "The sky is clear blue around you, except to your southeast, " +
	     "where you see strange dark and dirty clouds gathering.\n");
    add_item(({"clouds","dark clouds","strange clouds"}),
	     "The dark clouds is what the trails of smoke lead into, which " +
	     "you can see to your southeast.\n");
}

