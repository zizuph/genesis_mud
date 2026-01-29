/*
 * F71.c
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"

inherit BASEFOREST;

void
create_forest()
{
    set_long("   This is a narrow stretch of ground between two paths in the forest. "+
	"The bushes and trees spring up out of the ground on all sides, the shortest "+
	"bush coming to a point far above your head. To the north, you can see a path "+
	"that continues to the west, and it comes to a T-shaped intersection to the "+
	"south. A chill breeze blows north-south through the path, rustling the leaves "+
	"of the trees and causing the hanging vines to sway back and forth, sometimes "+
	"slapping up against you.\n\n");

    add_fexit(CORAMAR+"f72", "north", 0);
    add_fexit(CORAMAR+"f52", "south", 0);
}