/*
 * Woodsmen village in Mirkwood.
 * Varian 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_STD_DIR + "room";


void create_room()
{
    
    set_mirkwood_location(LOCATION_WEST_EDGE);
    
       

    set_short("The village of Weanting");
    
    set_long("The thick mass of black trees which fill Mirkwood forest have peeled " +
    	"away from you, save for one large oak tree in the middle of the clearing. " +
    	"A small dirt path wanders through the forest here, curving away " +
    	"to both the northwest and the south, where it seems to quickly vanish, " +
    	"hiding away from the " + VBFC("light_type") + " of the " + VBFC("day_desc") +
        " " + VBFC("sun_moon") + " that shines in this clearing. You also notice that " +
        "beside the oak tree, the path has a faint branch which winds up to the " +
        "wooden walls of a small village which sits atop the rocky rise which " +
        "rises up just west of the clearing. A sign is carved deeply into the trunk " +
        "of the oak tree, reading 'The Village of Weanting'. \n");

    add_item_light(({"moon","stars","sun","rising sun","setting sun","noon sun",
			"night stars", "night moon", "afternoon sun", "morning sun"}),
    	"Your eyes drink in the " + VBFC("light_type") + " from " +
    	"the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " as it shines " +
    	"brightly here, suddenly free of the shadows of Mirkwood.\n", LIGHT_ALL);
	add_item_light(({"tree", "oak tree", "oak", "large oak tree", "large oak"}),
	    "A massive black oak tree stretches out its branches majestically here, " +
	    "watching over everyone and everything which wanders along the dirt " +
	    "paths which pass beneath. Carved deeply into the black bark is a " +
	    "sign clearly reading 'The Village of Weanting', obviously naming " +
	    "the village which sits at the end of the small western trail which " +
	    "intersects the main path here.\n", LIGHT_ALL);
	add_item_light(({"sign", "carved sign"}),
	    "This sign is rather crude, as it is simply words carved " +
	    "roughly into the black bark of the large oak tree.\n", LIGHT_ALL);
	add_item_light(({"rise", "rocky rise", "western rise", "slope"}),
	    "A rocky rise juts up out of Mirkwood forest on the western edge " +
	    "of this clearing. A small trail branches off the main path and " +
	    "winds its way up the slope to the villge of Weanting which " +
	    "sits atop the rise.\n", LIGHT_ALL);
	add_item_light(({"village", "weanting", "Weanting"}),
	    "On the western edge of the clearing, the wooden walls of the " +
	    "village of Weanting are barely visible atop the rocky rise " +
	    "which reaches up out of Mirkwood forest. You could follow " +
	    "the small trail which branches off the main path here at " +
	    "the large oak tree in order to enter the village.\n", LIGHT_ALL);
	add_item_light(({"walls", "wooden walls", "village walls"}),
	    "Staring west, up to the top of the rocky rise, you can just" +
	    "make out the wooden walls which surround the village of " +
	    "Weanting. There is a small trail which branches off the " +
	    "main path here, it seems that if you were to follow it, " +
	    "it would lead you up the rise and into Weanting.\n", LIGHT_ALL);
	add_item_light(({"forest", "mirkwood", "Mirkwood"}),
	    "This is the legendary Mirkwood forest. There have always " +
	    "been stories of how dangerous this forest has been for " +
	    "the unwary traveller, and as you glance around at the " +
	    "forest which surrounds this clearing, you can understand why. " +
	    "You find it to be something of a relief to be free of Mirkwood's " +
	    "clutches for a moment as you enjoy the open air of the clearing.\n", LIGHT_ALL);
	add_item_light(({"road","path","ground", "trail"}),
	    "A well-worn dirt path branches out to the northwest and south " +
	    "here, in addition to curving up a rocky rise at the western edge " +
	    "of the clearing. There is a large oak tree growing where the paths " +
	    "intersect, with a sign carved into it which suggests that the village " +
	    "of Weanting sits atop the rise.\n", LIGHT_ALL);
	add_item_light(({"sky", "light", "up"}),
	    "You are actually able to see the sky here, unlike just about everywhere " +
	    "else in Mirkwood. The " + VBFC("light_type") + " from " +
	    "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " shines " +
	    "brightly, spraying its light across the entire clearing. \n",
	    LIGHT_ALL);
	add_item_light(({"shadow", "shadows"}),
	    "The forest of Mirkwood, which completely surrounds the clearing " +
	    "you are currently standing in, is full of sinister looking shadows " +
	    "which give you the impression they are looking for victims.\n", LIGHT_ALL);
	add_item_light(({"village", "weanting"}),
	    "The village of weanting sits atop a rocky rise which reaches up out " +
	    "of Mirkwood on the western edge of the clearing. From here, you can only " +
	    "make out the wooden walls which surround the village, but you " +
	    "could enter Weanting by following the path.\n", LIGHT_ALL);


    add_exit(WOODSMEN_DIR + "weanting2", "enter", "@@weanting@@");
    add_exit(WOODSMEN_DIR + "weanting2", "climb", "@@weanting@@",0,1);
    add_exit(WOODSMEN_DIR + "weanting2", "up", "@@weanting@@",0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r03/p08-r03", "northwest");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r03/f09", "north", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r03/f10", "northeast", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r04/f10", "east", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r05/f10", "southeast", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r05/p09-r05", "south");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r05/f08", "southwest", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r04/f08", "west", 0,0,1);
}
int
weanting()
{
    write("You feel slightly out of breath climbing west up the path into Weanting.\n\n\n");
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
    if((str != "sign")  && (str != "words") && (str != "tree") && (str != "carved sign"))
    { 
        notify_fail("Read what?\n");
        return 0;
    }
    write("The sign reads: The Village of Weanting. \n");
    SAYBB(" reads the sign.");
    return 1;
}

