/*
 * Room of the Old Road in Mirkwood.
 *
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";
inherit MIRKWOOD_STD_DIR + "room";


void create_room()
{
    
    set_mirkwood_location(LOCATION_MIDDLE);
    
       

    set_short("On top of a large boulder\n");
    
    set_long("You have managed to climb to the top of a rather large boulder, " +
    	"which has a triangular contour, with tips pointing north, east and " +
    	"west. Oddly enough, the surface of the boulder is rather flat. " +
    	"At the south edge of the boulder, you are able to observe traffic " +
    	"along the old forest road for some distance in both directions. " +
    	"The " + VBFC("light_type") + " from the " + VBFC("day_desc") +
        " " + VBFC("sun_moon") + " looks just a little stronger here than in " +
        "the rest of Mirkwood, but perhaps it just feels that way because you " +
        "finally have a little extra breathing room around you. \n");

    add_item_light(({"moon","stars","sun","rising sun","setting sun","noon sun",
			"night stars", "night moon", "afternoon sun", "morning sun"}),
    	"You can barely make out the " + VBFC("light_type") + " from " +
    	"the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " through " +
    	"the thick canopy of leaves overhead.\n", LIGHT_ALL);
    add_item_light(({"tree", "trees"}),
    	"Hovering over you, the trees of Mirkwood give you the " +
    	"strangest feeling that they are actually watching your every " +
    	"movement. The massive black trunks of the trees are all " +
    	"tangled in the underbrush. Occasionally, a slender " +
    	"ray of @@light_type@@ from the @@sun_moon@@ " +
    	"has been able to penetrate the eerie darkness of the trees, " +
    	"and it gives the impression that it is not quite as dark " +
    	"up here on this boulder as it was down on the old road. " + 
    	"Most of the time, however, the branches of the great trees " +
    	"wrap you in the darkness of the forest.\n", LIGHT_ALL);
	add_item_light(({"branch", "tree branch", "branches", "tree branches"}),
    	"The branches of the great trees of Mirkwood seems to reach " +
    	"out to hover over your head menacingly, striving to prevent " +
    	"any light from the @@sun_moon@@ from ever reaching " +
    	"your eyes.\n", LIGHT_ALL);
	add_item_light(({"trunk", "trunks", "tree trunk", "tree trunks", "bark"}),
	    "It seems that no matter which direction you look, you can see the dark " +
	    "bark of countless tree trunks. Most of the tree trunks are " +
	    "several feet wide, as you would expect in an old forest this " +
	    "large.\n", LIGHT_ALL);
	add_item_light(({"forest", "mirkwood", "Mirkwood"}),
	    "This is the legendary Mirkwood forest. There have always " +
	    "been stories of how dangerous this forest has been for " +
	    "the unwary traveller, and as you glance around, you can " +
	    "understand why.\n", LIGHT_ALL);
	add_item_light(({"leaf","leaves", "canopy"}),
	    "The leaves upon the trees of Mirkwood all seem to be " +
	    "exceptionally thick and lush, blocking almost every sign " +
	    "of the @@light_type@@ from reaching your eyes.\n", LIGHT_ALL);
	add_item_light(({"road","path","forest road","old forest road"}),
	    "Peering over the south edge of the boulder, you can " +
	    "see the worn collection of ancient paving stones " +
	    "which form the old forest road. At one time, the road ran " +
	    "from the old ford to the river running, where it " +
	    "then led to Erebor and the Iron hills. However, rumours " +
	    "suggest that now the road is only used by orcs and goblins, " +
	    "along with the occasional woodsmen.\n", LIGHT_ALL);
	add_item_light(({"stone","paving stone","paving stones", "stones"}),
	    "It is difficult to see much detail on these stones from " +
	    "up here on top of the boulder. It seems reasonably " +
	    "evident however, that these stones have been here for a " +
	    "very long time.\n", LIGHT_ALL);
	add_item_light(({"ground","boulder","surface", "boulder surface","rock", "flat surface"}),
	    "The surface of the boulder is almost uniformly flat, almost like " +
	    "a small plateau. From what you can see, it appears to be solid rock. " +
	    "A charred spot near the northern tip suggests that not are you not " +
	    "the first to visit the top of this boulder, but that someone has " +
	    "used it as a campsite in times past.\n",
	    LIGHT_ALL);
	add_item_light(({"underbrush", "bushes", "brush", "bush", "shrub", "shrubs"}),
	    "Aside from the occasional animal trails or man-made paths, the " +
	    "forest floor seems to be absolutely littered with all manner of " +
	    "bushes and shrubs. Most of these patches of undergrowth would be " +
	    "difficult to pass through easily, even from your vantage point " +
	    "on top of this boulder, you cannot see a clear path through " +
		"the brush anywhere.\n",
	    LIGHT_ALL);
	add_item_light(({"sky", "light", "up"}),
	    "With the massive trees blocking almost all semblance of natural" +
	    " light, it is almost impossible for you to even see the" +
	    " @@daylight_desc@@ from here. Perhaps you might be able" +
	    " to find a tree which you could climb up to see more details?\n",
	    LIGHT_ALL);
	add_item_light(({"shadow", "shadows"}),
	    "Almost everywhere you look, the tall, black trees of Mirkwood " +
	    "create deep and ominous shadows which might be better left " +
	    "unexplored.\n", LIGHT_ALL);
	add_item_light(({"tip", "tips"}),
	    "While the surface of this boulder is rather flat, its contours are " +
	    "somewhat triangular in shape, tapering out into somewhat pointed tips " +
	    "which point to the north, west and east. Which tip did you want to look " +
	    "at? The north tip, the west tip or the east tip?\n", LIGHT_ALL);
	add_item_light(({"charred spot","spot","campfire","char"}),
	    "A circular charred spot near the northern tip of the boulder shows that " +
	    "somebody, at some point in time, built a campfire here. Nothing but a " +
	    "black circle remains now however.\n", LIGHT_ALL);
	add_item_light(({"north tip","north", "northern tip"}),
	    "The northern tip of the boulder reaches out into Mirkwood forest, and " +
	    "it is draped in deeper shadows than the rest of the boulder as a result. " +
	    "a small charred circle suggests the remains of a campfire here at some " +
	    "point in time.\n", LIGHT_ALL);
	add_item_light(({"eastern tip","east tip","east"}),
	    "The eastern tip of the rock runs alongside the old forest road. Walking " +
	    "near the edge, you can see the old road running off into the distance " +
	    "east of here.\n", LIGHT_ALL);
	add_item_light(({"western tip","west tip","west"}),
	    "The western tip of the rock runs alongside the old forest road. Walking " +
	    "near the edge, you can see the old road running off into the distance " +
	    "towards the Anduin, west of here.\n", LIGHT_ALL);






    add_exit("r14", "down");
}

