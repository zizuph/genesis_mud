
/*
 * BT3.c
 * BellTower in the Monk Ruins
 * - Alaron January 1997
 */

#include "default.h"

inherit "/std/room";

void
create_room()
{
  set_short("Tower Landing");
  set_long("   You are on the narrow, circular walkway which surrounds "+
	   "the staircase in the center of the room. The staircase is "+
	   "an ancient, iron relic long since fallen victim to rust "+
	   "and decay. A thin stone walkway jutting out of the walls "+
	   "of the room provides your only method for moving around "+
	   "here in any direction other than up or down. As you peer "+
	   "up through the hole in the ceiling through which the stairs "+
	   "climb, you notice an incredibly large bell hanging from "+
	   "iron and wood beams and ropes thicker than most men.\n\n");

  add_prop(ROOM_I_INSIDE, 1);

  add_item( ({"narrow walkway", "walkway", "circular walkway", 
		"narrow circular walkway", "stone walkway",
		"thin walkway", "thin stone walkway"}),
	    "The thin, stone walkway which juts out from the "+
	    "base of the walls here is part of the ceiling of "+
	    "the room below. It is narrow and potentially dangerous. "+
	    "It circles an ancient, decaying iron stairwell that "+
	    "leads up and down out of here.\n");

  add_item( ({"staircase", "stairwell", "decaying staircase",
		"iron staircase", "iron stairwell", "rusted staircase",
		"rusted stairwell"}),
	    "The rotting, rusted iron stairwell in the middle of the "+
	    "room is an ancient relic. The steps where people once "+
	    "walked comfortably on wooden planks are now nothing more "+
	    "than the iron frames beneath, barely distinguishing this "+
	    "construction from a ladder.\n");

  add_item( ({"hole", "ceiling", "floor", "down", "up"}),
	    "There is a hole in each of the ceiling and floor. The "+
	    "decaying iron staircase winds up and down through "+
	    "these holes.\n");

  add_exit(MONKRUIN_DIR + "bt4", "up");
  add_exit(MONKRUIN_DIR + "bt2", "down");
}
