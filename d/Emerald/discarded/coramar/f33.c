/*
 * F33.c
 * Coramar Forest, room containing an altar.
 * - Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"
#include <stdproperties.h>

inherit BASEFOREST;

int
get_altar(string str)
{
    if (str == "altar")
    {
       write("The altar is far too heavy to lift. It is made from a single, "+
	"three-meter-wide piece of heavy wood!\n");
        return 1;
    }
    return 0;
}

int push_altar(string str)
{
    if (str == "altar")
    {
       write("You push with all your might on the altar, but it is far too "+
	"heavy to budge, even on the moist grass surface below.\n");
       return 1;
    }
    return 0;
}

int pray_to(string str)
{
    if (str == "altar")
    {
        write("You get on your knees and worship before the altar, but "+
		"nothing happens.\n");
	return 1;
    }
    return 0;
}

void
create_forest()
{

    set_long("   A cool breeze blows across the small forest clearing, yet the "+
	"thick blanket of hovering gray mist seems unaffected by the wind. All around "+
	"the gray, shadowy outlines of immense tree trunks spring out of the "+
	"ground beyond the mist and reach high above into the forest canopy. The "+
	"path continues through the forest heading northwest and southeast. On the "+
	"northwest side of the path, the tall bushes, vines and grass have been "+
	"cut back and maticulously groomed to form a soft, square bed of short grass "+
	"roughly five meters wide and three meters deep. Positioned squarely in the "+
	"center of the grass clearing is an enormous altar constructed of dark, "+
	"red-tinged wood.\n\n");

    add_item( ({"clearing", "square", "bed", "short grass", "grass"}),
	"The square clearing of short grass has been maticulously groomed. All of the "+
	"blades of grass are exactly the same height. To achieve something like this "+
	"in a fertile, moist environment like this where vegetation springs up "+
	"overnight would be a tremendous feat. Plant grooming like this would require "+
	"daily effort. Placed squarely in the middle of the clearing is a large, "+
	"red-tinged wooden altar.\n");

    add_item( ({"altar", "wooden altar", "red-tinged altar", "wood", "wood altar",
	"large altar", "large wood altar"}),
	"The altar in the center of the grass clearing is quite impressive. It is made "+
	"of a dark, reddish wood that has the appearance of strength and durability. "+
	"Simply lookin at the wood gives you the impression that it is dense and "+
	"heavy. Upon closer inspection, you see that there are no seams, no tack or "+
	"nail marks, no evidence of a clay or mud sealant of any kind. This altar, which "+
	"spans nearly three meters in width, is carved from a single piece of wood! "+
	"You also notice that its surface is smooth and has been treated with a "+
	"liquid of some kind that has hardened and bonded with the wood, protecting "+
	"it from the water. You have never seen anything like it before. The surface "+
	"is smooth, unmarred and unstained. This leads you to believe that the altar "+
	"is probably used for ceremonies rather than sacrifices.\n");

    add_fexit(CORAMAR+"f34", "southeast", 0);
    add_fexit(CORAMAR+"f32", "northwest", 0);
}

init()
{
    ::init();
    add_action(get_altar, "get");
    add_action(push_altar, "push");
    add_action(pray_to, "pray");
    add_action(pray_to, "worship");
}
