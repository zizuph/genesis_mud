/* camp_1 -  entrance into camp*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/tyr/tyr.h"

void create_room()
{
	set_short("Inside the Aarakocra's trading camp.");
	
	set_long("You slip between the booths to a more private area where no wares are displayed. "+
		"There are several cots lying on the ground where the Aarakocra obviously sleep. Tents "+
		"have been set up to store additional goods that haven't been displayed yet. \n");
	
	add_item(({"tents", "tent"}), "The tents are made out of some kind of white fabric "+
		"that is soft to the touch and seems to reflect the bright sunlight, keeping "+
		"the inside of the tent fairly cool. \n");
	
	add_item( ({"fabric"}), "The fabric is made out of something that you've never "+
		"encountered before. When you take a closer look, you can see that its a woven "+
		"fabric that shimmers in the light. You wonder what it could be made out of to "+
		"make it shine like that. \n");
	
	add_item( ({"cots", "cot"}), "The cots are all neatly made since all of the "+
		"Aarakocra are working in the booths. \n");
	
	add_item(({"ground"}), "There are remanants of breakfast are still scattered "+
		"around the cots. It looks like the Aarakocra eat mostly fruit judging by "+
		"the various pits and rinds on the ground. \n");
 
    OUTSIDE
    ADD_SUN_ITEM
	ADD_ZIG_ITEM;

	add_exit(TYR_TCAMP+"camp_15.c", "north", 0, 1);
    add_exit(TYR_TCAMP+"camp_3.c", "west", 0, 1);
}
