/*
 * F38.c
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
    set_long("   You are at a junction of several forest paths. A cool breeze "+
	"blows across the area, rustling the tall leaves and bushes and "+
	"causing the thick, hanging vines to sway back and forth across "+
	"the path. The vines drop low, almost to the forest floor. A "+
	"well-travelled path leads into the blue-gray shadows to the north, while "+
	"another path leads east and yet another leads to the southwest.\n\n");

    add_fexit(CORAMAR+"f37", "north", 0);
    add_fexit(CORAMAR+"f65", "east", 0); 
    add_fexit(CORAMAR+"f39", "southwest", 0);
}