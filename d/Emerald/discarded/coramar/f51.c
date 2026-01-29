/*
 * F51.c
 * Another section of a trail in the Coramar forest.
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
    set_long("   The tangle of trails, paths and trees in the forest seems to "+
	"go on forever in endless circles of confusion. The thick, swirling fog "+
	"distorting the view of the forest behind a sheen of gray further adds to the "+
	"confusion and mystery. The trail here is bordered by shoulder-height bushes and "+
	"other strange-looking plants as well as hundreds of vines hanging suspended "+
	"in the air by tree limbs so far above they aren't visible. A cool breeze "+
	"blows around the curve of the trail from the southwest and continues, rustling "+
	"the leaves on the plants to the east.\n\n");

    add_fexit(CORAMAR+"f52", "east", 0);
    add_fexit(CORAMAR+"f50", "southwest", 0);
}