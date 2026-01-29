/*
 * F56.c
 * Room containing one of the animal traps which Thanduin checks periodically
 * in his wanderings.
 * Note that if baseforest is not loaded before this room is, this room will
 * not have a short description. This should be fine, since baseforest will be
 * loaded when a player first enters the forest.
 * - Alaron Feb 1998
 */

#include "dirheader.h"
#include "coramar.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASETRAPROOM;

void
create_traproom()
{
    set_long("   This section of the misty forest seems more open and less crowded "+
	"by the massive trees. Tall, shoulder-height shrubs, ferns and bushes crowd "+
	"around the edges of the narrow forest path. Thick, tangled vines hang down "+
	"from the limbs of the giant trees above. Occasionally a small rabbit will "+
	"dart out of the brush and scamper across the path to the safety of the greenery "+
	"on the other side. The path continues in a meandering path through the forest "+
	"and amazingly tall bushes to the west and south.\n\n");

    add_fexit(CORAMAR+"f73", "west", 0);
    add_fexit(CORAMAR+"f71", "south", 0);
}
