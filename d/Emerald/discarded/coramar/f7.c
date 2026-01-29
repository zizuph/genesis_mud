/*
 * F7.c
 * A section of a main path through the coramar forest.
 * - Alaron Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("    Standing in the middle of a large clearing in the forest, you can "+
	"look around and see trails leading off in virtually every direction. The "+
	"thick cloud of dark mist hovering over the forest prevents you from seeing "+
	"very far or navigating reliably. Just to the northwest, beyond a fallen branch, "+
	"there is a small clearing partially hidden behind the veil of mist. Trails "+
	"continue throughout the wood to the northeast, east, and southwest.\n\n");    

    add_item( ({"fallen branch", "branch"}) ,
	"The branch on the ground in the middle of the trail leading northwest to "+
	"the clearing is black, moist and covered in moss, indicating that it must "+
	"have fallen quite some time ago.\n");

    add_fexit(CORAMAR+"f11", "northwest", 0);
    add_fexit(CORAMAR+"f12", "northeast", 0);
    add_fexit(CORAMAR+"f10", "east", 0);
    add_fexit(CORAMAR+"f5", "southwest", 0);
}
