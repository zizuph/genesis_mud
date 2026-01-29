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
    
    set_mirkwood_location(LOCATION_WEST_EDGE);
    
       

    set_short("The village of Weanting");
    
    set_long("You are standing in the middle of Weanting, which is a " +
    	"small village that is obviously home to several woodsmen in " +
    	"the middle of Mirkwood. A stout wooden wall encircles the " +
    	"entire village which sits atop a tall rocky rise, jutting " +
    	"up out of Mirkwood forest. The village itself is mostly a " +
    	"collection of simple wooden shacks, which provides only the most " +
    	"basic shelter for the various woodsmen families. There are " +
    	"three larger buildings here which catch your eye, they appear " +
    	"to have some importance.\n");

    add_item_light(({"moon","stars","sun","rising sun","setting sun","noon sun",
		"night stars", "night moon", "afternoon sun", "morning sun"}),
    	"Your eyes drink in the " + VBFC("light_type") + " from " +
    	"the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " as it shines " +
    	"all over the village of Weanting.\n", LIGHT_ALL);
	add_item_light(({"forest", "mirkwood", "Mirkwood"}),
	    "This is the legendary Mirkwood forest. There have always " +
	    "been stories of how dangerous this forest has been for " +
	    "the unwary traveller. Here in the village of Weanting, " +
	    "you are able to take a brief respite from your travels " +
	    "in Mirkwood.\n", LIGHT_ALL);
	add_item_light(({"road","path","ground", "down"}),
	    "There are several, well-worn dirt paths crossing through the " +
	    "village of Weanting. While most of them connect the shacks " +
	    "and buildings of the village itself, they eventually " +
	    "combine into one larger path which leads through the eastern " +
	    "wall, down the forest of Mirkwood below.\n", LIGHT_ALL);
	add_item_light(({"sky", "light", "up"}),
	    "You are actually able to see the sky here, unlike just about everywhere " +
	    "else in Mirkwood. The " + VBFC("light_type") + " from " +
	    "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " shines " +
	    "brightly, spraying its light across the entire village. \n",
	    LIGHT_ALL);
	add_item_light(({"shadow", "shadows"}),
	    "The forest of Mirkwood, which completely surrounds the village" +
	    "you are currently standing in, is full of sinister looking shadows " +
	    "which give you the impression they are looking for victims.\n", LIGHT_ALL);
	add_item_light(({"village", "weanting"}),
	    "You are standing in the middle of Weanting, which is a " +
    	"small village that is obviously home to several woodsmen in " +
    	"the middle of Mirkwood. A stout wooden wall encircles the " +
    	"entire village which sits atop a tall rocky rise, jutting " +
    	"up out of Mirkwood forest. The village itself is mostly a " +
    	"collection of simple wooden shacks, which provides only the most " +
    	"basic shelter for the various woodsmen families. There are " +
    	"three larger buildings here which catch your eye, they appear " +
    	"to have some importance.\n", LIGHT_ALL);
	add_item_light(({"buildings","houses","shacks", "shelters", "building", "house", "shack", "shelter"}),
	    "There are dozens of tiny shacks here, dwellings for the woodsmen who " +
	    "live inside Mirkwood forest. These houses are all made of wood and " +
	    "are just big enough to give a small family enough room to eat and " +
	    "sleep. You can also see three larger buildings scattered amidst " +
	    "the houses.\n", LIGHT_ALL);
	add_item_light(({"large buildings","larger buildings","three buildings"}),
	    "Standing above the smaller shacks in Weanting, you can see three " +
	    "larger buildings. The first to the north appears to be a general store and the " +
	    "second to the south, a small post office. The last, and most popular of the three, " +
	    "appears to be the local tavern which is on the west side of the village. \n", LIGHT_ALL);
	add_item_light(({"post office", "post", "small post office","west building", "second building"}),
	    "At the south end of the village stands a wooden building which appears " +
	    "to be the local post office. While it is not very large by most standards, " +
	    "it is still one of the largest buildings in this small village.\n", LIGHT_ALL);
	add_item_light(({"tavern", "inn", "third building", "south building"}),
	    "This is the largest, and by all appearances the most popular, building " +
	    "in the entire village of Weanting. A sign outside proclaims this to " +
	    "be 'The Wild Boar Inn'. Sitting on the west side of the village, " +
	    "this would be a good place for you to visit if you are a little " +
	    "hungry or thirsty.\n", LIGHT_ALL);
	add_item_light(({"sign","wooden sign"}),
	    "This wooden sign sits in the front of a large building at the west " +
	    "end of the village. The sign reads 'The Wild Boar Inn' and " +
	    "has a picture of a large boar, tusks thrust up into the air, " +
	    "standing proudly in front of a large mug of ale.\n", LIGHT_ALL);
	add_item_light(({"store", "shop","north building", "general store", "first building"}),
	    "This large building has been built near the northern edge of the village, " +
	    "and appears to be to general store which services the village of Weanting. " +
	    "As best you can estimate from here, this store seems to offer all sorts " +
	    "of basic supplies.\n", LIGHT_ALL);
	add_item_light(({"wall", "wooden wall"}),
	    "This wall is made from sharpened stakes of wood. It would probably " +
	    "not do much good against a large army, but it keeps the woodsmen " +
	    "of Weanting safe from spiders or small bands of orcs.\n", LIGHT_ALL);
	add_item_light(({"rise", "rocky rise"}),
	    "The village of Weanting sits atop a singular rocky rise which " +
	    "thrusts up above the trees of Mirkwood. This rise, in addition " +
	    "to the wooden walls surrounding the village, provide the woodsmen " +
	    "some much needed protection.\n", LIGHT_ALL);

    add_exit(WOODSMEN_DIR + "weanting1", "east", "@@mirk@@");
    add_exit(WOODSMEN_DIR + "weant_inn", "south", "@@inn@@");
    add_exit(WOODSMEN_DIR + "weant_post", "west", "@@post@@");
    add_exit(WOODSMEN_DIR + "weant_shop", "north", "@@shop@@");
    add_exit(WOODSMEN_DIR + "weant_inn", "open", "@@open@@",1,1);
    add_exit(WOODSMEN_DIR + "weant_shack", "enter", "@@shack@@", 1,1);

}
int
mirk()
{
write("You carefully make your way down the rocky path and back into Mirkwood.\n\n\n");
return 0;
}
int
shack()
{
write("You think about entering one of the shacks here, but you soon " +
	"understand that nobody is letting you into their personal home.\n\n" +
	"You find yourself back in the middle of Weanting.\n");
return 1;
}
int
post()
{
write("\n\nYou make your way over to the west side of the village to visit " +
	"the post office.\n\n");
return 0;
}
int
shop()
{
write("\n\nWandering though the north end of the village, you quickly duck " +
	"into the general store.\n\n");
return 0;
}
int
inn()
{
write("\n\nYou open the door to the Wild Boar Inn and slip inside.\n\n");
return 0;
}
int
open()
{
write("\n\nYou open the door to the Wild Boar Inn, however someone " +
	"from inside closes it again for you. You can enter the inn " +
	"by going south.\n\n");
return 1;
}