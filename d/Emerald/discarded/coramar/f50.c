/*
 * F50.c
 * Part of a trail in the coramar forest.
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
    set_long("   The trail rounds a gradual curve here. The bushes and other "+
	"growth bend inward over the trail in what looks like an attempt to swallow "+
	"it whole. A cool breeze blows through the area from the west to the east. Looking "+
	"around, you notice that various other parts of the trail are experiencing "+
	"breezes, but most are blowing in different directions. Even more startling is "+
	"that the thick bank of fog hovering over the forest floor is moving slowly "+
	"in directions completely opposite the wind. The trail continues its gradual "+
	"curve to the northeast and straightens to the west.\n\n");

    add_fexit(CORAMAR+"f51", "northeast", 0);
    add_fexit(CORAMAR+"f10", "west", 0);
}