/*
 * Gairent in Mirkwood.
 * Varian 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";
inherit MIRKWOOD_STD_DIR + "room";


void create_room()
{
    
    set_short("The village of Gairent");
    set_long("You find yourself in the middle of a small village which " +
    	"sits at the bottom of a narrow valley within Mirkwood forest. " +
    	"A low, wooden wall encircles the village with only one gate " +
    	"in the west side which leads back up to Mirkwood forest. There " +
    	"are a small handful of shacks scattered around the village, with " +
    	"three more prominent buildings which stand out. At the north " +
    	"end of the village, bright firelight radiates from the smithy " +
    	"of the local blacksmith. Judging from the dried herbs hanging " +
    	"in the windows, the small hut to the east is the place of business " +
    	"for the local herbalist. However, the most popular building in this " +
    	"village clearly seems to be the tavern which sits up against the " +
    	"southern wall beside a small tent.\n");

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
	    "There are several, well-worn dirt paths crossing through the " +
	    "village of Gairent. While most of them connect the shacks " +
	    "and buildings of the village itself, they eventually " +
	    "combine into one larger path which leads through the western " +
	    "gate before climbing the ravine and leading back into " +
	    "Mirkwood forest.\n", LIGHT_ALL);
	add_item_light(({"sky", "light", "up"}),
	    "You are actually able to see some of the sky here, unlike just " +
	    "about anywhere else in Mirkwood. The " + VBFC("light_type") + 
	    "from the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " shines " +
	    "brightly, shedding its light across the entire village. \n",
	    LIGHT_ALL);
	add_item_light(({"shadow", "shadows"}),
	    "The forest of Mirkwood, which completely surrounds the village" +
	    "you are currently standing in, is full of sinister looking shadows " +
	    "which give you the impression they are looking for " +
        "victims.\n", LIGHT_ALL);
	add_item_light(({"village", "gairent"}),
	    "You are standing in the middle of Gairent, which is a " +
    	"small village that is obviously home to several woodsmen in " +
    	"the middle of Mirkwood. A stout wooden wall encircles the " +
    	"entire village which sits at the bottom of a valley, hidden " +
    	"deep in Mirkwood forest. The village itself is mostly a " +
    	"collection of simple wooden shacks, which provides only the most " +
    	"basic shelter for the various woodsmen families. There are " +
    	"three larger buildings here which catch your eye, they appear " +
    	"to have some importance.\n", LIGHT_ALL);
	add_item_light(({"buildings","houses","shacks", "shelters", "building", 
            "house", "shack", "shelter"}),
	    "There are dozens of tiny shacks here, dwellings for the woodsmen " +
	    "who live inside Mirkwood forest. These houses are all made of wood " +
	    "and are just big enough to give a small family enough room to eat " +
	    "and sleep. You can also see three larger buildings scattered amidst " +
	    "the houses.\n", LIGHT_ALL);
	add_item_light(({"large buildings","larger buildings","three buildings"}),
	    "Standing above the smaller shacks in Gairent, you can see three " +
	    "larger buildings. The first to the north appears to be the smithy " +
	    "of the local blacksmith, while a hut to the east seems to be owned " +
	    "by a herbalist. The largest and most popular of the buildings " +
	    "in Gairent is the Rusty Axe Tavern, which is pressed up against the " +
        "southern wall of the village. \n", LIGHT_ALL);
	add_item_light(({"smithy", "blacksmith", "blacksmith's smithy", 
            "first building", "north building"}),
	    "The bright firelight and the rythmic hammering of metal suggests " +
        "that this building is where the local blacksmith runs his business. " +
        "In fact, given the cool air in this valley, it might not be a bad " +
        "idea to go north and visit the smithy, it almost " +
	    "feels like you can feel the warmth from here.\n", LIGHT_ALL);
	add_item_light(({"tavern", "inn", "third building", "south building", 
            "rusty axe", "rusty axe tavern"}),
	    "This is the largest, and by all appearances the most popular, " +
        "building in the entire village of Gairent. The sign posted above " +
        "the door proclaims this building to be the home of the Rusty Axe " +
        "Tavern, by all appearances, a comfortable, if rustic, place for " +
        "the hard working woodsmen to take their leisure.\n", LIGHT_ALL);
	add_item_light(({"sign","wooden sign"}),
	    "This wooden sign sits in the front of a large building at the south " +
	    "end of the village. The sign reads 'The Rusty Axe Tavern' and " +
	    "displays the image of an rusty axe lodged into a tree stump while " +
	    "a woodsman sits beside it, hoisting a mug of ale.\n", LIGHT_ALL);
	add_item_light(({"hut", "herbalist", "herbalist hut", "east building", 
            "second building"}),
	    "You can see strings of dried herbs hanging inside this hut, which " +
	    "in clearly the home of a local herbalist. You appear to be welcome " +
	    "to go inside for a visit.\n", LIGHT_ALL);
	add_item_light(({"wall", "wooden wall"}),
	    "The low, wooden wall which surrounds the village of Gairent is " +
        "not very tall, but since the village is set at the bottom of a " +
        "valley, you do not imagine these walls would have much military " +
        "value. If you had to speculate, the wall is primarily there to " +
        "prevent some of the wildlife from straying into the village " +
        "proper.\n", LIGHT_ALL);
	add_item_light(({"vale", "valley", "ravine"}),
	    "This village is set at the bottom of a valley, where a small, " +
        "shallow stream winds its way through Mirkwood forest. The steep " +
        "walls of the ravine help keep the community of Gairent somewhat " +
        "secluded.\n", LIGHT_ALL);
	add_item_light(({"water", "stream", "creek"}),
	    "This stream might better be defined as a creek, as had you not " +
        "stopped in Gairent, you would never have likely noticed it. The " +
        "creek runs along the floor of the valley, beside the eastern wall " +
        "of Gairent before it continues west towards the Anduin " +
        "River.\n", LIGHT_ALL);
	add_item_light(({"river", "anduin"}),
	    "You cannot see the Anduin river from here, you are in the middle " +
        "of Mirkwood forest! However, the small creek which runs alongside " +
        "the village likely empties into the Anduin " +
	    "at some point.\n", LIGHT_ALL);
    add_item_light(({"tent", "small tent"}),
        "This small tent sits just east of the tavern, you should be able " +
        "to enter it quite easily by going southeast.\n", LIGHT_ALL);

    add_exit("gairent1", "out", "@@mirk@@",0,1);
    add_exit("gairent1", "up", "@@mirk@@",0,1);
    add_exit("gairent1", "west", "@@mirk@@");
    add_exit("gairent_tavern", "open", "@@door@@",0,1);
    add_exit("gairent_tavern", "south", "@@tavern@@");
    add_exit("gairent_herb", "east", "@@herb@@");
    add_exit("gairent_forge", "north", "@@smithy@@");
    add_exit("gairent_adv", "southeast", "@@tent@@");
    add_exit("gairent_shack", "enter", "@@shack@@", 1,1);

}
int
mirk()
{
write("You pass through the wooden gate in the walls of Gairent.\n\n\n "+
	"Following the narrow path which climbs up the side of the " +
	"valley, you find yourself back into the gloom of Mirkwood forest.\n\n\n");
return 0;
}
int
shack()
{
write("You think about entering one of the shacks here, but you soon " +
	"understand that nobody is letting you into their personal home.\n\n " +
	"You find yourself back in the middle of Gairent.\n");
return 1;
}
int
door()
{
write("\n\nYou open the door to the tavern but it is not long before " +
	"someone closes it. You can just go south if you want to be " +
	"inside.\n\n");
return 1;
}
int
tavern()
{
write("You open the door to the tavern and slip inside.\n\n");
return 0;
}
int
herb()
{
write("\n\nA strong herbal scent envelops your nose as you enter the small hut.\n\n");
return 0;
}
int
smithy()
{
write("\n\nA warm rush of hot air surrounds you as you step into the smithy.\n\n");
return 0;
}
int
tent()
{
write("\n\nYou crouch down a little as you duck under the open flap and " +
    "enter the small tent.\n\n");
return 0;
}