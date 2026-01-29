/*
 * Woodsmen village in Mirkwood.
 * Varian 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";
inherit MIRKWOOD_STD_DIR + "room";


void create_room()
{
    
    set_mirkwood_location(LOCATION_WEST_EDGE);
    
       

    set_short("On a small path in Mirkwood forest.");
    
    set_long("You are currently at the edge of a deep valley somewhere " + 
    	VBFC("location_desc") + " of Mirkwood forest. A narrow path winds " +
    	"up out of the valley before disappearing into the gloom of the woods " +
    	"somewhere to the north. Faint light from the " + VBFC("light_type") + 
    	" of the " + VBFC("day_desc") +" " + VBFC("sun_moon") + " manages to " +
    	"weave its way through the trees, illuminating what appears to be " +
    	"a small woodsmen village which is nestled at the bottom of the " +
    	"valley. Thick underbrush gathers around the trees in every " +
    	"other direction, making any passage into the forest rather " +
    	"difficult. You notice a small wooden sign which has been mounted " +
    	"on a nearby tree.\n");

    add_item_light(({"moon","stars","sun","rising sun","setting sun","noon sun",
			"night stars", "night moon", "afternoon sun", "morning sun"}),
    	"Your eyes drink in the " + VBFC("light_type") + " from " +
    	"the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " as it shines " +
    	"down into the valley below.\n", LIGHT_ALL);
	add_item_light(({"tree", "oak tree", "oak", "large oak tree", "large oak"}),
	    "A massive black oak tree stretches out its branches majestically here, " +
	    "watching over everyone and everything which wanders along the dirt " +
	    "paths which pass beneath. Mounted on the trunk of this tree is a " +
	    "sign which clearly indicates that the village of Gairent rests in " +
	    "the valley below.\n", LIGHT_ALL);
	add_item_light(({"sign", "small sign", "small wooden sign", "wooden sign"}),
	    "This small sign has been securely mounted on the trunk of a nearby " +
	    "oak tree. The sign simply reads 'Village of Gairent' giving a name " +
	    "to the village in the valley below.\n", LIGHT_ALL);
	add_item_light(({"vale", "deep valley", "valley"}),
	    "This deep valley drops down below you, falling away from " +
	    "the rest of the forest floor. The narrow path you are currently on " +
	    "winds its way down to a small village which is neslted at the " +
	    "very bottom.\n", LIGHT_ALL);
	add_item_light(({"village", "gairent", "Gairent"}),
	    "The path you are walking along winds its way down the side of " +
	    "the valley and through low wooden walls, into a small woodsmen " +
	    "village. Wispy curls of smoke drift up into the air, clearly " +
	    "showing that the village is inhabited, perhaps even awaiting " +
	    "any visitors who might be travelling nearby. You can enter the " +
	    "the village by following the path down into the valley.\n", LIGHT_ALL);
	add_item_light(({"smoke", "curls", "wispy curls of smoke"}),
	    "Curling up into the " + VBFC("day_desc") + " air are " +
	    "faint wisps of smoke, no doubt rising from the home fires " +
	    "which have been lit in the village in the valley below.\n", LIGHT_ALL);
	add_item_light(({"walls", "low walls", "wooden walls", "village walls"}),
	    "You can see some low, wooden walls which surround the village of " +
	    "Garient below you. They would certainly not be very effective " +
	    "against an army, but they likely serve well to keep the wildlife " +
	    "away from the village proper.\n", LIGHT_ALL);
	add_item_light(({"forest", "mirkwood", "Mirkwood"}),
	    "This is the legendary Mirkwood forest. There have always " +
	    "been stories of how dangerous this forest has been for " +
	    "the unwary traveller, and as you glance around at the " +
	    "forest which surrounds this clearing, you can understand why. " +
	    "You find it to be something of a relief to be free of Mirkwood's " +
	    "clutches for a moment as you enjoy the open air of the clearing.\n", LIGHT_ALL);
	add_item_light(({"road","path","ground", "trail"}),
	    "A well-worn dirt path comes from the village of Gairent, winding up " +
	    "and out of the valley before you before trailing off to the north, " +
	    "seemingly swallowed up by the gloom of Mirkwood forest.\n", LIGHT_ALL);
	add_item_light(({"sky", "light", "up"}),
	    "You are actually able to see some of the the sky here, unlike just about " +
	    "everywhere else in Mirkwood. The " + VBFC("light_type") + " from " +
	    "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " shines " +
	    "its light across the village at the bottom of the valley below you. \n",
	    LIGHT_ALL);
	add_item_light(({"shadow", "shadows"}),
	    "The forest of Mirkwood, which completely surrounds the valley " +
	    "you are currently standing near, is full of sinister looking shadows " +
	    "which give you the impression they are looking for victims.\n", LIGHT_ALL);
	

    add_exit("gairent2", "enter", "@@gairent@@");
    add_exit("gairent2", "down", "@@gairent@@",0,1);
    add_exit("gairent2", "follow", "@@gairent@@",0,1);
    add_exit("/d/Gondor/rhovanion/mirkwood/south_forest/r10/p08-r10", "northwest", 0,0,1);
    add_exit("/d/Gondor/rhovanion/mirkwood/south_forest/r10/f09", "north", 0,0,1);
    add_exit("/d/Gondor/rhovanion/mirkwood/south_forest/r10/f10", "northeast", 0,0,1);
    add_exit("/d/Gondor/rhovanion/mirkwood/south_forest/r11/f10", "east", 0,0,1);
    add_exit("/d/Gondor/rhovanion/mirkwood/south_forest/r12/f10", "southeast", 0,0,1);
    add_exit("/d/Gondor/rhovanion/mirkwood/south_forest/r12/f09", "south", 0,0,1);
    add_exit("/d/Gondor/rhovanion/mirkwood/south_forest/r12/f08", "southwest", 0,0,1);
    add_exit("/d/Gondor/rhovanion/mirkwood/south_forest/r11/f08", "west", 0,0,1);
}
int
gairent()
{
    write("You follow the path as it winds down deep into the valley below.\n\n\n");
    return 0;
}

void
init()
{
    ::init();
    add_action("do_read","read");
}
int
do_read(string str)
{
    if(!str)
    {
        notify_fail("Read what?\n");
        return 0;
    }
    if((str != "sign")  && (str != "small sign") && (str != "small wooden sign") && (str != "wooden sign"))
    { 
        notify_fail("Read what?\n");
        return 0;
    }
    write("The sign reads: The Village of Gairent. \n");
    SAYBB(" reads the sign.");
    return 1;
}
