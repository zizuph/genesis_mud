/*
 * F36.c
 * Part of the non-obvious, slightly hidden section of the coramar forest.
 * Alaron - March 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You are standing between two high walls of ferns, bushes and "+
	"tangled vines. Thick, twisted vines hang down from the unseen branches in "+
	"the forest canopy high above. A cool, wet breeze blows across the trail, "+
	"rustling the leaves and bushes and making the vines sway back and forth. The "+
	"path continues into the mist to the east, and toward a towering wall of "+
	"green to the west.\n\n");

    add_item( ({"wall", "green wall", "towering wall", "towering wall of green",
	"wall of green"}),
	"The wall is huge, the top is hidden behind a veil of dark, blue-gray mist. You "+
	"can't quite make out the details of it from here, but it looks like a massive "+
	"tangle of bushes, leaves and vines.\n");

    add_exit(CORAMAR+"f37", "east", 0);
    add_exit(CORAMAR+"f35", "west", 1);
}