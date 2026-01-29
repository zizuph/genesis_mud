/*
 * F32
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You are on a narrow path leading through a mist-shrouded forest. The "+
	"mist hangs low above the forest floor, bathing everything with a thick, "+
	"blue-gray blanket that hides the trees, plants and grass in shadows. Huge "+
	"plants spring forth out of the ground on either side of the path, coming "+
	"to a point high above your head. The huge trunks of trees appear as nothing "+
	"more than vague, giant black cylinders in the distance behind the fog. Thick, "+
	"twisting vines hang down onto the path from hidden branches and limbs "+
	"above. The path continues into the mist to the northwest and southeast. To the "+
	"northwest, you can make out the faint outline of a black iron fence surrounding "+
	"a clearing. To the southeast, you can see the misty image of a light-colored "+
	"stone structure of some kind.\n\n");

    add_item( ({"fence", "iron fence", "black fence", "black iron fence"}),
	"The black iron fence is too far away to see clearly through this fog.\n");

    add_item( ({"structure", "stone structure", "light stone structure",
	"light-colored structure", "light-colored stone structure"}),
	"The stone structure appears to be rectangular, and there are possibly "+
	"some decorations on it, but you can't make out any more detail than that "+
	"from this vantage point. Getting closer through the fog might help some.\n");

    add_fexit(CORAMAR+"f31", "northwest", 0);
    add_fexit(CORAMAR+"f33", "southeast", 0);
}