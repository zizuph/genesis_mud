/*
 * F41.c
 * Part of the non-obvious, slightly hidden section of the coramar forest.
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You are standing alongside an enormous wall of vines, trees and "+
	"hundreds of forms of plant life. Vines spring forth out of the ground and "+
	"hang from trees with thousands of other plants using the vines like a "+
	"trellace, supporting their weight. The mass containing thousands of "+
	"shades of green appears impenetrable to the naked eye. The path continues "+
	"out from the all to the east amid far more subtle vegetation and into the "+
	"murky gray fog.\n\n");

    add_item( ({"wall", "vegetation" ,"wall of green", "wall of vegetation", "big wall",
	"plant life", "shades of green", "greenery", "green"}),
	"The massive, towering wall of overgrown vegetation reaches so far into the "+
	"sky that the mist obscures its top behind its gray veil. It strikes you almost "+
	"as an optical illusion. For all of the height that it boasts, it is quite "+
	"thin, and you can almost see the other side to the west.\n");



    add_exit(CORAMAR+"f40", "east", 0);
    add_exit(CORAMAR+"f42", "west", 1);
}