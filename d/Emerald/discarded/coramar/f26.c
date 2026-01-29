/*
 * f26.c
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
    set_long("   You are standing in the middle of a crossing of forest paths. Huge, "+
	"overgrown bushes and other plants reach high into the hovering mist, surrounding "+
	"the path in a box of green. The moist, damp earth of the forest floor leads "+
	"to the northeast, toward a low, iron fence. The path continues into the "+
	"mirky gray of the forest to the south and to the west.\n\n");

    add_item( ({"fence", "low fence", "iron fence", "low iron fence"}),
	"You can't quite make it out from here.\n");

    add_fexit(CORAMAR+"f27", "northeast", 0);
    add_fexit(CORAMAR+"f62", "south", 0);
    add_fexit(CORAMAR+"f25", "west",0);
}