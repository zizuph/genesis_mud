
/*
 * BT2.c
 * Bell Tower in the Monk Ruins
 * - Alaron January 1997
 */

#include "default.h"

inherit "/std/room";

void
create_room()
{
  set_short("A decaying, ruined stone room");
  set_long("   You are standing in the middle of a decaying, ruined "+
	   "stone room. The floor is made of hard, cold stone and is "+
	   "littered with pieces of broken wood, dirt, grime, and other "+
	   "assorted stains which have appeared from ages of neglect. The "+
	   "ceiling is riddled with cracks and chips of missing stone. The "+
	   "center of the room is dominated by an ancient, rusted iron "+
	   "stairwell which circles up through a carved hole in the "+
	   "ceiling. A shattered, cracked doorway leads into another "+
	   "room to the west.\n\n");
  
  add_prop(ROOM_I_INSIDE, 1);

  add_item( ({"floor", "ground", "down", "stains", "dirt",  "grime",
		"dust"}),
	    "The floor of the room is cold, hard stone. It is filled "+
	    "with cracks, chips and broken pieces of stone. Atop the "+
	    "cracked floor is a layer of dirt, grime, and stains created "+
	    "by ages of sitting untended in the surrounding moisture.\n");

  add_item( ({"stone", "cold stone", "hard stone", "cold hard stone"}),
	    "The cold, hard stone of the room is ancient. It is covered "+
	    "with hideous black and green stains from ages of sitting "+
	    "untended, open to the surrounding moisture. Cracks line "+
	    "the surface of nearly all the stone.\n");

  add_item( ({"up", "ceiling", "hole", "circle"}),
	    "The ceiling is cracked and drooping on some places. A large "+
	    "circle is cut out of the dull, grey stone in the ceiling, "+
	    "allowing the rusted iron staircase passage to the level "+
	    "above.\n");
  
  add_item( ({"stairs", "staircase", "iron stairs", "iron staircase",
		"rusted stairwell", "stairwell", "rusted iron stairwell"}),
	    "A narrow, rusted iron stairwell circles up through the "+
	    "stone ceiling into the levels above. You wonder if the "+
	    "staircase is even sturdy enough to climb.\n");

  add_exit(MONKRUIN_DIR + "bt3", "up", "@@shaky_up@@");
  add_exit(MONKRUIN_DIR + "bt1", "west", 0);
}

int
shaky_up()
{
  write("You carefully climb up the stairs, flinching each time you "+
	"place your foot down and cause an ear-splitting creaking "+
	"noise ... \n\n");
  say(QCTNAME(TP)+" carefully climbs up the stairs, flinching each "+
      "time the stairs squeak and strain under the weight.\n");
  return 0;
}

