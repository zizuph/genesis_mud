inherit "/std/room";
inherit "/lib/pub";

#include "/d/Roke/common/defs.h"

void
init()
{
   ::init();
   init_pub();
}

create_room()	{
	set_short("Dragons Head Tavern");
	set_long(BSS("You have entered a noisy inn in the southwestern "+
		"parts of Tyr. You can see a small counter here, and "+
		"the people who are here, are mostly common citizens "+
		"of Tyr. There is a sign on the wall you can read for "+
		"instructions.\n"));

	add_item(({"counter","small counter"}), BSS(
		"This is a rather small counter, just wide enough to "+
		"hold your drinks.\n"));

	add_item("sign", BSS(
		"There is some writing on it, maybe you could read it?\n"));

	add_cmd_item("sign","read",BSS(
     "Welcome! Drink as much as you like, stay as long as you like! "+
   "\n")+"There is a menu under "+
		"the sign.\n");

	add_item("menu","This is a menu, it contains a list of drinks!\n");

	add_cmd_item("menu","read","	The menu of Dragons Head "+
		"Tavern:\n"+
	"\n"+
	"		Ale     :     8 copper coins\n"+
	"		Beer    :    12 copper coins\n"+
	"		Wine    :    55 copper coins\n"+
	"		Special :    76 copper coins\n"+
	"		Whiskey :   260 copper coins\n"+
	"\n\n	Please don't touch the waitress!\n");

	add_exit(SUL_STR+"road4","north",0);

   
   add_drink(({ "ale", "tiny ale" }), "ale", "tiny",
      70, 4, 8, 0, 0, "It's very dark but smells like beer.\n",
      0);
   add_drink(({ "beer", "small beer" }), "beer", "small",
      100, 6, 12, 0, 0, "It's a small but refreshing beer.\n", 0);
	add_drink(({ "wine", "blue wine" }), "wine", "blue",
	   50, 35, 55, 0, 0, "It is a light blue whine, surely "+
	   "smells good!\n", 0);
   add_drink( "special", "special", 0,
      62, 25, 76, 0, 0, "It's the special of the house.\n",
      0);
   add_drink(({ "whiskey", "malt whiskey" }), "whiskey", "malt",
      84, 50, 260, 0, 0, "It is a fine malt whiskey, surely not brewed around here.\n", 0);
}

