/*
 * tower1.c
 *
 * Skippern 20(c)02
 *
 * A large hall inside a noble house.
 *
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <stdproperties.h>

void
create_inside()
{
    set_short("the first level in a tower");
    set_long(
		"You are standing in a large, square room at the base of a "+
		"high tower. "+
		"It smells faintly of herbs and flowers in here, and of the "+
		"beeswax used to polish the marble floor. "+
		"Every footstep, every rustle of your clothing, seems to echo "+
		"in this stark space, which is barren of any furnishings save "+
		"four pedestals standing in each corner. "+
	    "Through the open doorway you can see west into the lovely "+
		"garden, while a steep staircase on the far wall leads up.\n");
			 

	add_item( ({ "pillar", "pillars", "bust", "busts", "head", "heads", 
		"king", "kings", "pedestal", "pedestals" }), 
		"There are four pedestals located in the corners " +
		"of the room. Each of the pillars contains busts of some old " +
		"kings of Gondor. In the north corner resides Isildur, the east " +
		"is Turambar in honor of his conquests, to the south is Minardil " +
		"in memory of his death, and finally in west is Valacar, whose "+
		"Rhovanion wife cost him the support of many Dunedain.\n");
	add_item( ({"north", "north bust", "isildur", "Isildur", "north pedestal" }),
		"In the north corner resides the bust of Isildur, bearded and "+
		"wavy of hair. He was the son of Elendil and brother to Anarion, "+
		"and the High King of Gondor and Arnor. Isildur cut the One Ring "+
		"from Sauron's hand during the War of the Last Alliance.\n");
	add_item(({ "south", "south bust", "Minardil", "minardil", "south pedestal"}),
		"In the south corner resides the youthful bust of ill-fated King Minardil, "+
		"son of Hyarmendacil II and father of King Telemnar. He was killed at "+
		"Pelargir when the Corsairs of Umbar attacked.\n");
	add_item(({"east", "east bust", "turambar", "Turambar", "east pedestal"}),
		"In the east corner is the bust of the hard-faced and elderly-looking "+
		"Turambar of House Anarion, who reigned over Gondor for 126 years and "+
		"conquered Rhun and the East-lands.\n");
	add_item(({"west", "west bust", "valacar", "Valacar", "west pedestal"}),	
		"In the west corner is the bust of a rather sad-looking Valacar, "+
	    "the 20th king of Gondor. He married Vidumavi, also known as "+
		"Galadwen, the daughter of the King of Rhovanion, which caused "+
		"considerable unrest as she was of the short-lived race of men. "+
		"Concerned that the blood of his heir, Eldacar, was "+
		"tainted, the coastal provinces rebelled and a civil war known as "+
		"the Kin-Strife broke out once Valacar died.\n");
	add_item(({"walls", "tower walls"}),
		"The walls are of the same marble as the floor, and polshed to a "+
		"high sheen. They are completely bare and unremarkable.\n");
	add_item(({"garden", "garden door", "doorway"}),
		"A doorway leads west into the garden, which appears to be well-"+
		"maintained.\n");
	add_item(({"stair", "staircase", "stairwell", "stairs"}),
		"A steep set of stairs leads toward the upper floors of the tower.\n");
	add_item(({"floor", "floors", "marble floors", "marble floor"}),
		"The room is floored in a beautiful marble that has been polished "+
		"to a high-sheen with beeswax.\n");
	add_item(({"beeswax", "wax"}),
		"It makes the marble surfaces gleam.\n");
	add_cmd_item("air", "smell", "It smells faintly of the herbs and flowers "+
		"growing in the garden outside, and the faintest hint of beeswax.\n");
	
		
    add_exit(DOL_HILLS + "g-11/garden3", "west", 0, 1);
    add_exit(DOL_HILLS + "g-11/tower2", "up", 0, 1);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}


