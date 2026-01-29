/*
 * f62.c
 * Coramar Forest
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{

    set_long("   You are at a junction of several forest paths. A cool breeze "+
	"blows across the area, rustling the tall leaves and bushes and "+
	"causing the thick, hanging vines to sway back and forth across "+
	"the path. The vines drop low, almost to the forest floor. A "+
	"well-travelled path leads north, and two more lead to the east and "+
	"southwest. Peering southeast through the trees and above the thick "+
	"wall of bushes, you can see the dark gray outline of what looks to "+
	"be one cliff face of a huge plateau.\n\n");

    add_item( ({"face", "cliff", "plateau", "cliff face", "huge plateau"}),
	"The side of the plateau is hardly visible through the murky grayness "+
	"of the fog. It might be easier to distinguish from a closer vantage "+
	"point.\n");

    add_fexit(CORAMAR+"f26", "north", 0);
    add_fexit(CORAMAR+"f63", "east", 0);
    add_fexit(CORAMAR+"f66", "southwest", 0);
}