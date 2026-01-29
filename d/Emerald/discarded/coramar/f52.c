/*
 * F52.c
 * Intersecting path in the coramar forest.
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
    set_long("   You are standing at a large intersection of two trails in this "+
	"mist-covered forest. One trail, large and wide and bordered on both sides "+
	"by immense growth leads off to the north, while the other leads east and "+
	"west of here. A cool breeze blows from west to east here, rustling leaves "+
	"and blowing between trees, creating an eerie whistling noise that sends "+
	"a chill down your spine. The dark blanket of mist shrouds the entire forest "+
	"floor in its gray moisture, hiding great, colorful tree trunks and thick, "+
	"green branches in dark shadows.\n\n");


    add_fexit(CORAMAR+"f71", "north", 0);
    add_fexit(CORAMAR+"f53", "east", 0);
    add_fexit(CORAMAR+"f51", "west", 0);
}