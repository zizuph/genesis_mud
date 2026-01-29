/*
 * MNaple Tree - Gairent.
 * April 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_STD_DIR + "room";

int climb_tree(string str);

void create_room()
{
    
    set_short("Atop the maple tree");
    set_long("You are sitting at the top of a tree which grows in the " +
    	"side yard of the blacksmith's forge in Garient. You can " +
    	"see the tiny village of Gairent spread out below you, and " +
    	"the dark, imposing Mirkwood forest beyond. There is really " +
    	"nowhere to go from here except back down.\n");

    add_item_light(({"moon","stars","sun","rising sun","setting sun","noon sun",
		"night stars", "night moon", "afternoon sun", "morning sun"}),
    	"Your eyes drink in the " + VBFC("light_type") + " from " +
    	"the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " as it shines " +
    	"all over the village of Gairent.\n", LIGHT_ALL);
	add_item_light(({"forest", "mirkwood", "Mirkwood"}),
	    "This is the legendary Mirkwood forest. There have always " +
	    "been stories of how dangerous this forest has been for " +
	    "the unwary traveller. Here in the village of Gairent, " +
	    "you are able to take a brief respite from your travels " +
	    "in Mirkwood.\n", LIGHT_ALL);
	add_item_light(({"road","path","ground", "down"}),
	    "While you are currently stuck inside the fenced yard, " +
	    "there are several, well-worn dirt paths crossing through the " +
	    "village of Gairent. Most paths connect to the shacks " +
	    "and buildings of the village itself, before they eventually " +
	    "combine into one larger path which leads through the western " +
	    "gate before climbing the ravine and leading back into " +
	    "Mirkwood forest.\n", LIGHT_ALL);
	add_item_light(({"sky", "light", "up"}),
	    "You are actually able to see some of the sky here, unlike just about " +
	    "anywhere else in Mirkwood. The " + VBFC("light_type") + " from " +
	    "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " shines " +
	    "brightly, shedding its light across the entire village. \n",
	    LIGHT_ALL);
	add_item_light(({"shadow", "shadows"}),
	    "The forest of Mirkwood, which completely surrounds the village" +
	    "you are currently standing in, is full of sinister looking shadows " +
	    "which give you the impression they are looking for victims.\n", LIGHT_ALL);
	add_item_light(({"village", "gairent"}),
	    "You are currently in the village of Garient, a small village of " +
	    "woodsmen hidden deep within Mirkwood forest. Several shacks are " +
	    "scattered inside the village wall, with three larger buildings " +
	    "standing out.\n", LIGHT_ALL);
	add_item_light(({"buildings","houses","shacks", "shelters", "building", "house", "shack", "shelter", }),
	    "There are dozens of tiny shacks here, dwellings for the woodsmen who " +
	    "live inside Mirkwood forest. These houses are all made of wood and " +
	    "are just big enough to give a small family enough room to eat and " +
	    "sleep. The village forge is very close, as you are currently up a tree " +
	    "in the forge's side yard. At the south end of the village, you can see " +
	    "what appears to be the local tavern.\n", LIGHT_ALL);
	add_item_light(({"forge", "blacksmith", "blacksmith's forge", "wall", "west wall"}),
	    "The blacksmith's forge is a very important building in a small village like " +
	    "Garient. You are currently standing in the yard of the forge, and can " +
	    "enter the forge proper by going through the narrow doorway to the west.\n", LIGHT_ALL);
	add_item_light(({"yard", "blacksmith's yard"}),
	    "This is a small yard east of the " +
    	"forge in Gairent. Scattered across the yard are several " +
    	"barrels, boxes, crates and assorted items too numerous " +
    	"to count. In the middle of the yard, a large cart rests " +
    	"up against the tall, slender maple tree you climbed. To the west, the " +
    	"wall of the forge is unbroken save for a narrow doorway. " +
    	"A low wooden fence surrounds the rest of the yard, making " +
    	"your only way out back into the forge.\n", LIGHT_ALL);
	add_item_light(({"cart", "woodcart", "wood cart", "large cart", "wooden cart"}),
	    "This wooden cart is sitting up against the base of this tree.\n", LIGHT_ALL);
	add_item_light(({"tree", "slender tree", "maple tree"}),
	    "This is the tree you are currently sitting in.\n", LIGHT_ALL);
	add_item_light(({"board", "boards", "boards on cart"}),
	    "There are several boards used in the construction of the cart, but you " +
	    "cannot see them very well from here.\n", LIGHT_ALL);
	add_item_light(({"nail", "nails", "nails in boards"}),
	    "You seem to remember that you saw the boards of the cart were nailed in, " +
	    "but you cannot see any details from here.\n", LIGHT_ALL);
	add_item_light(({"barrel", "barrels"}),
	    "There are several stout, wooden barrels scattered around the yard, some of which " +
	    "seem to hold some rainwater inside.\n", LIGHT_ALL);
	add_item_light(({"water", "rainwater"}),
	    "It looks like some of the barrels have some water inside, but you cannot " +
	    "see any details while up in this tree.\n", LIGHT_ALL);
	add_item_light(({"crate", "crates", "box", "boxes"}),
	    "There are several boxes and crates scattered around the yard, often arranged in " +
	    "tidy stacks. The boxes and crates are mostly empty, although a few of them " +
	    "are filled with assorted junk that the blacksmith probably should have thrown " +
	    "away, but for some reason has decided to keep.\n", LIGHT_ALL);
	add_item_light(({"door", "doorway"}),
	    "There is a narrow doorway in the wall of the forge, leading back inside.\n", LIGHT_ALL);
	add_item_light(({"items", "assorted items", "junk", "assorted junk"}),
	    "The blacksmith apparently uses this side yard as additional storage for anything " +
	    "he would like to keep, but does not have space for. You get the distinct feeling " +
	    "that he is a bit of a packrat.\n", LIGHT_ALL);
	add_item_light(({"fence", "wooden fence", "low fence"}),
	    "This is a low fence made from wooden logs, which encircles the blacksmiths yard. " +
	    "You cannot see many more details from high up in this tree.\n", LIGHT_ALL);

    add_exit("yard", "down");
}    


void

init()
{
	::init();
	add_action("climb_tree", "climb");
}

int
climb_tree(string str)
{
	if(!str)
	{
		write("Climb where? Down?\n");
		return 1;
	}
	if((str != "tree") && (str != "down") && (str != "down tree"))
	{ write("Climb what?\n");
	return 1;
	}
	write("You climb down the tree, back to the yard below.");
	TP->move_living("M","/d/Gondor/rhovanion/mirkwood/woodsmen/yard.c",1,0);
	SAYBB(" climbs down out of the maple tree.");
	return 1;
}
