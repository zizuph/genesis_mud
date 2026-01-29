/*
 * F73.c
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
    set_long("   You are on a meandering path through the mist-shrouded forest. A "+
	"cool breeze blows across the path, rustling the tall foliage on either "+
	"side and causing the thick, hanging vines to sway back and forth. The vines "+
	"hang down nearly to the forest floor from unseen branches high above in the "+
	"forest canopy. The huge trees seem to be everywhere, the thick fog turning "+
	"them into ominous, distant shadows. The path continues to a fork west of here, "+
	"and curves south at a point just east of here.\n\n");

    add_fexit(CORAMAR+"f72", "east", 0);
    add_fexit(CORAMAR+"f55", "west", 0);
}