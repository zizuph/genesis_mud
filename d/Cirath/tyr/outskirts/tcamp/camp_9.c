/* camp_1 -  entrance into camp*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/tyr/tyr.h"

void create_room()
{
	set_short("Inside the Aarakocra's trading camp.");
	
	set_long("The bright sun beats down on you as soon as you walk "+
		"around the market. The booths were set up by the Aarakocra "+
		"traders in order to showcase their wares while they wait for "+
		"King Kalek to approve the trade agreements with their elders. \n");
	
	add_item(({"booths", "booth", "market"}), "As you glance around at all the booths, you can tell "+
		"that the Aarakocra have brought out all of their best goods to entice "+
		"King Kalek into agreeing to trade. The booths have an array of items "+
		"made from the trademark items from the village of ice and feathers. You "+
		"wonder how the ice isn't melting in the harsh desert heat!\n");
	
	add_item( ({"item", "wares", "good", "goods"}), "As expected, the goods for sale are made of "+
		"Winter's Nest's trademark exports of ice and feathers. There looks to be quills and fans from feathers, "+
		"as well as musical instruments, bottles and sculptures made out of ice.\n");
	
	add_item(({"bird", "trader", "traders", "birds"}), "The Aarakocra stands between 7 and 8 feet tall "+
		"and has black eyes and a grey beak with a wing span of at least 20 feet. "+
		"At the center of each wing is a three-fingered hand with an opposable thumb.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
	ADD_ZIG_ITEM;

    add_exit(TYR_TCAMP+"camp_10.c", "north", 0, 1);
	add_exit(TYR_TCAMP+"camp_4.c", "south", 0, 1);
    add_exit(TYR_TCAMP+"camp_16.c", "east", 0, 1);
    add_exit(TYR_TCAMP+"camp_8.c", "west", 0, 1);
}
