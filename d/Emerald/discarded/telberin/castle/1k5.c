/*
 * 1k5.c
 * This is the kitchen on the first floor of Castle Telberin 
 * Unsure of who the original coder is
 * Re-description/Items added by Alaron August 16, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();

    set_short("Kitchen");
    set_long("   You are overpowered by the sounds of clanking pots, "+
	     "pans and mixing tools as well as the luxurious smells "+
	     "of freshly baking breads, pastries and steaming vegetables. "+
	     "The kitchen is remarkably clean considering it appears that "+
	     "this one facility has the unenviable task of feeding the whole "+
	     "of the castle. There is a large fire stove in the far wall "+
	     "with pots of boiling water hanging from an iron bar above "+
	     "while varying sizes of pots and pans rest on a rack "+
	     "over the fire. A small door allows a quick glance into "+
	     "the storage room to the west. Another door leads out "+
	     "into the central courtyard.\n\n");
    
    add_item( ({"pots", "pans", "dishes", "stove", "fire stove", "water",
                "boiling water", "iron bar", "bar", "rack", "fire"
}),
	     "Dozens of various sizes of pots and pans rest over the "+
	     "incredibly hot stove. A thick, black iron bar supports "+
	     "heavy pots filled with boiling water for stews and "+
	     "other delicious-smelling meals.\n");

    add_item( ({"small door", "door", "storage room", "west"}),
	     "You take a quick glance into the storage room, and "+
	     "don't see anything particularly intriguing. It is a "+
	     "storage room filled with various supplies for the "+
	     "kitchen.\n");

    add_item( ({"north", "another door", "central courtyard",
		"courtyard"}),
	     "The calm, peaceful beauty of the courtyard is visible "+
	     "from the entryway into the kitchen to the north. There "+
	     "is a large fountain adorning the center of the courtyard.\n");

    add_exit(CASTLE_DIR + "1k9","north");
    add_exit(CASTLE_DIR + "1k6","west");
}

