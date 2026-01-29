/*
 * 1k6.c
 * This is the kitchen's storage room.
 * Unsure who original author is.
 * Updated/Redescribed/Items Added   Alaron August 16, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Storage room");
    set_long("   Standing in the middle of a stuffy, cold storage room, "+
	     "you look at the heavy, wooden shelves surrounding you. They "+
	     "are stocked with bags of spices, seeds, seasonings, salt, "+
	     "sugars and countless other items in jars, crates and "+
	     "woven bags. All along the north wall are large crates "+
	     "and heavy-looking barrels. Above the door back to the "+
	     "kitchen is a small ledge.\n\n");

    add_item( ({"heavy wooden shelves", "shelves", "wooden shelves",
		"heavy shelves"}),
	     "The shelves are stocked with bags of spices, seeds, "+
	     "seasonings, salt, and many, many other things stored "+
	     "in jars, crates or woven bags. The kitchen storage "+
	     "room looks well-prepared for the task of feeding "+
	     "an entire castle.\n");

    add_item( ({"crates", "barrels", "large crates", "heavy-looking barrels",
		"heavy barrels"}),
	     "The north wall is nearly covered with crates and barrels. "+
	     "Some of the barrels are easily recognizable as wine "+
	     "casks, but the rest are unlabelled.\n");

    add_item( ({"ledge", "small ledge"}),
	     "There is a small ledge over the door leading back "+
	     "into the kitchen. Atop it is a small figurine.\n");

    add_item( ({"figurine", "small figurine"}),
	     "The small figurine depicts the image of Telan-Ri, apparently "+
	     "set here to keep watch over the food storage.\n");

    add_exit(CASTLE_DIR + "1k5","east");
}



