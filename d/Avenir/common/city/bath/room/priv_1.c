#pragma strict_types
/*
 * ~/priv_1.c
 *
 * Private room in Melchior's Bath.
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Lilith, Apr 2002: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../priv.h"
inherit BATH_PRIV;

static void
create_priv_bath(void)
{
    set_short("Southwest private bath");
    set_long("A perfect example of understated luxury, this room "+
	"is made entirely of kesoit wood, the scent of which "+
	"permeates the room. The floor is of wooden slats spaced "+
	"to allow water through so that footing does not become "+
	"slippery. On each wall hangs a painting depicting scenes "+
	"from nature. The walls are smooth as skin, panelled with "+
	"hand-planed wood that requires no oil or finish to "+
	"maintain its lustrous texture. From a sculpted stone "+
	"spout warm water trickles into a large round tub, also "+
	"made of kesoit. Warmth and moisture envelope you, "+
	"inviting you to cast off your cares and abandon yourself "+
	"to the pleasure of bathing. There is a sign on the door.\n");

    add_item(({"wood", "kesoit"}),
	"A fine-grained, reddish wood related to the fragrant cedar "+
	"and cypress, it is known to grow only in Sybarus.\n");
    add_item(({"wall", "walls", "panelling", "panels"}),
	"The walls are panelled in fragrant kesoit wood that "+
	"has been hand-planed to a remarkable smoothness."+
	"Each wall is hung with a painting.\n");
    add_item(({"light", "crystal"}),
	"Built into the ceiling is a large, faceted chunk of the glowing "+
	"crystal which those native to Sybarus call ''The Source''.\n");
    add_item(({"painting","paintings"}),
	"There are painting on each of the walls, try looking at "+
	"them individually.\n");
    add_item(({"north wall", "north painting"}),
	"This painting is a still-life of a single white orchid "+
	"arranged in a slender vase against a pale green background.\n");
    add_item(({"east wall", "east painting"}),
	"This painting depicts the god Hizarbin half-rising from "+
	"the sea.\n");
    add_item(({"west wall", "west painting"}),
	"This painting is an overview of the islands of Sybarus.\n");
    add_item(({"south wall", "south painting"}),
	"This is a depiction of a small island upon which grows a "+
	"stand of mighty trees towering over grazing goats.\n");

    add_cmd_item("wall", "touch", "It feels silky smooth to the touch.\n");

    bath_door("one", "arc_sw", "ne");
}

public void
hook_smelled(string str)
{
    write("The air smells strongly of something similar to cedar.\n");
}
