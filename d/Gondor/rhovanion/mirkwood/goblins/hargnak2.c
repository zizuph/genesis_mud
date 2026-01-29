/*
 * Village of Hargnak.
 * Varian - June 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";
inherit MIRKWOOD_STD_DIR + "room";


void create_room()
{
    
    set_mirkwood_location(LOCATION_EAST_EDGE);
    
       

    set_short("The village of Hargnak");
    
    set_long("You are standing in the middle of the village of Hargnak in " +
        "Mirkwood forest. A loose collection of poorly constructed shacks " +
        "have been tossed around this hilltop in a rather haphazard fashion. " +
        "Most of the buildings appear to be homes for the residents of the " +
        "village, yet there are four which stand out in particular to your " +
        "eye. A wide stone building sits to the north, serving as the post " +
        "office of Hargnak while nearby to the east, an even larger stone " +
        "building appears to be the local watering hole, the Chipped Mug " +
        "Tavern. To the west you spot dozens of war banners decorating a " +
        "long wooden building, while to the south a well-maintained wooden " +
        "store speaks to the prosperity of a local merchant. A rugged " +
        "stone wall surrounds the rest of the village, the only opening " +
        "running through a narrow wooden gate to the northwest. \n");

    add_item_light(({"moon","stars","sun","rising sun","setting sun","noon sun",
		"night stars", "night moon", "afternoon sun", "morning sun"}),
    	"Your eyes drink in the " + VBFC("light_type") + " from " +
    	"the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " as it shines " +
    	"all over the village of Hargnak.\n", LIGHT_ALL);
	add_item_light(({"forest", "mirkwood", "Mirkwood", "tree", "trees", 
        "gloom", "shadows", "darkness"}),
	    "This is the legendary Mirkwood forest. There have always " +
	    "been stories of how dangerous this forest has been for " +
	    "the unwary traveller. It is possible that the goblins who " +
        "live here in Hargnak have something to do with that " +
        "reputation.\n", LIGHT_ALL);
	add_item_light(({"road","path","ground","down"}),
	    "Several muddy paths wind their way around the various shacks and " +
        "buildings in a somewhat disorganized fashion.\n", LIGHT_ALL);
	add_item_light(({"sky", "light", "up"}),
	    "You are actually able to see the sky here, unlike almost everywhere " +
	    "else in Mirkwood. The " + VBFC("light_type") + " from " +
	    "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " shines " +
	    "brightly, spraying its light across the entire village. \n",
	    LIGHT_ALL);
	add_item_light(({"village", "hargnak"}),
	    "You are standing in the middle of the village of Hargnak in " +
        "Mirkwood forest. A loose collection of poorly constructed shacks " +
        "have been tossed around this hilltop in a rather haphazard fashion. " +
        "Most of the buildings appear to be homes for the residents of the " +
        "village, yet there are four which stand out in particular to your " +
        "eye. A wide stone building sits to the north, serving as the post " +
        "office of Hargnak while nearby to the east, an even larger stone " +
        "building appears to be the local watering hole, the Chipped Mug " +
        "Tavern. To the west you spot dozens of war banners decorating a " +
        "long wooden building, while to the south a well-maintained wooden " +
        "store speaks to the prosperity of a local merchant. A rugged " +
        "stone wall surrounds the rest of the village, the only opening " +
        "running through a narrow wooden gate to the northwest.\n", LIGHT_ALL);
	add_item_light(({"buildings","houses","shacks", "shelters", "building", 
        "house", "shack", "shelter"}),
	    "Dozens of wooden shacks, all in various states of repair, have " +
        "been scattered around the village of Hargnak. They appear to be " +
        "mostly houses and shelters for the residents, although a few " +
        "larger buildings stand out amongst them.\n", LIGHT_ALL);
	add_item_light(({"large buildings","larger buildings","four buildings"}),
	    "There are four larger buildings which stand out in the village, " +
        "roughly standing at the north, east, south and west sides of " +
        "Hargnak.\n", LIGHT_ALL);
	add_item_light(({"west building", "second building"}),
	    "Dozens of war banners surround this long, wooden building. You " +
        "would surmise that this is a hall for the goblins who serve " +
        "as the warriors of Hargnak.\n", LIGHT_ALL);
	add_item_light(({"third building", "south building"}),
	    "This tall, well-mainted building is quite obviously a store in " +
        "the hands of a very prosperous local merchant. There is no doubt " +
        "that this building is of the finest construction, obviously a " +
        "rare sight for the goblins of Hargnak.\n", LIGHT_ALL);
	add_item_light(({"north building","first building"}),
	    "This wide building is one of two which has been constructed from " +
        "the dark grey stone of this rocky hilltop. The building appears " +
        "to be the local outlet for the Genesis postal service, which " +
        "enables travellers around the donut to maintain communication " +
        "with each other.\n", LIGHT_ALL);
    add_item_light(({"east building","fourth building"}),
        "This massive building is the largest in the village and only one " +
        "of two which has been constructed out of stone. A large arch has " +
        "been carved out of the front wall, allowing you to see the " +
        "interior of a much visited tavern, the Chipped Mug.\n", LIGHT_ALL);
	add_item_light(({"wall", "stone wall", "rugged stone wall"}),
	    "The tall wall of the village has been ruggedly cut and hewn from " +
        "a dark grey stone. The wall certainly looks as if it would do an " +
        "excellent job of defending the village from any assault.\n", LIGHT_ALL);
	add_item_light(({"hill", "rocky hill", "hilltop"}),
	    "The village of Hargnak has been built on the top of a tall, rocky " +
        "hill which juts up from the darkness and the gloom of Mirkwood " +
        "forest.\n", LIGHT_ALL);
    add_item_light(({"banner", "banners", "war banner", "war banners"}),
        "Dozens of ragged war banners have been hung around the long " +
        "wooden building which sits on the western edge of the village.\n", LIGHT_ALL);
    add_item_light(({"gate", "narrow gate", "wooden gate"}),
        "This narrow wooden gate is rather sturdy and well made, and it " +
        "seems to provide the only means of access " +
        "back into the black gloom of Mirkwood forest.\n", LIGHT_ALL);

    add_exit(GOBLINS_DIR + "hargnak1", "northwest", "@@mirk@@");
    add_exit(GOBLINS_DIR + "harg_shop", "south");
    add_exit(GOBLINS_DIR + "harg_adv", "west");
    add_exit(GOBLINS_DIR + "harg_post", "north");
    add_exit(GOBLINS_DIR + "harg_inn", "east");
    add_exit(GOBLINS_DIR + "harg_shack", "enter", "@@shack@@", 1,1);

}
int
mirk()
{
write("You carefully make your way down the rocky hill and back into Mirkwood.\n\n\n");
return 0;
}
int
shack()
{
write("You think about entering one of the shacks here, but you soon " +
	"understand that nobody is letting you into their personal home.\n\n" +
	"You find yourself back in the middle of Hargnak.\n");
return 1;
}
