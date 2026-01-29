/*
 * f63
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
    set_long("   You are standing in the middle of a turning point in a narrow, "+
	"mist-shrouded forest path. The path continues from here to the southeast "+
	"toward a small clearing and to the west. Southeast, in the clearing, it almost "+
	"looks like you can see a little bit of sunshine peeking through a hole in the "+
	"canopy far above. Peering through the trees and bushes to the south, you can "+
	"make out the dark, ominous outline of the cliff face of a huge plateau.\n\n");

    add_item(({"cliff face", "face", "plateau", "dark outline", "ominous outline",
	"outline", "huge plateau", "south"}),
	"The dark, ominous outline of the huge plateau is barely visible through the "+
	"mass of trees, bushes and other forest growth. Maybe you can maneuver to "+
	"get a closer look at the cliff face?\n");

    add_fexit(CORAMAR+"f64", "southeast", 0);
    add_fexit(CORAMAR+"f62", "west", 0);
}