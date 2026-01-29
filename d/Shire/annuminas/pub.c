/*
* Vladimir 11-12-94
*/
inherit "/d/Shire/room";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include <money.h>
#define TO this_object()
#define TP this_player()
/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */

create_room()
{
   set_short("Pub");
   set_long(
	"This is a small bar that is used by the inhabitants of "
	+"Annuminas to get good quality food and drinks from."
   +" A poorly written menu covers a hole in the wall, "
   +"you should read it if you are able. "
	+" Eat and drink at your own risk, the brutes who eat here "
	+"have been known to suffer ill side effects.\n");

   add_cmd_item("menu", "read", "@@read");

   add_prop(ROOM_I_INSIDE,1);

   add_drink( ({ "beer", "beers"}),
      "beer", "tasty", 75, 20, 30, 0, 0,
      "An extremely tasty beer.\n", 0);
   add_drink( ({ "ale", "ales", "watered down", "watered down ale" }),
      "ale", "watery", 200, 20, 72, 0, 0,
      "It is just old ale that has been watered down.\n", 0);
   add_food( ({ "stew", "stews" }),
    "hobbit", "warm", 85, 80, 0, 0,
      "It looks hairy, yet nourishing, yet repulsive all in one.\n", 0);
   add_food( ({ "steak", "steaks" }),
      "elf", "raw", 65, 80, "elf steak",
      "steaks",
      "It looks like steak... Wait a minute, was that a finger?\n", 0);
    add_food( ({"manure", "manures", "dung", "crap"}),
	"manure", "cow", 110, 105, 0, 0,
	"It is far from hard to tell what this is.\n");
  add_exit(ANNUM_DIR + "amc5", "north");

}

/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
   ::init(); /* Since it's a room this must be done. */
   add_action("do_read", "read");
   init_pub();
}

/*
* Function name: read
* Description:   Read the menu
* Arguments:     str - hopefully the menu
*/
int
do_read(string str)
{
   if(str = "menu")

  write("" +
      "   Tasty Beer                30 cc\n" +
      "   Watered down ale          72 cc\n" +
      "   Warm Hobbit Stew          80 cc\n" +
      "   Raw Elf Steak             80 cc\n" +
	"   Cow Manure               105cc\n" +
      "Try 'buy beer with gold' if you wanna specify what to\n" +
      "pay with, or 'test buy beer' to see what would happen\n" +
      "if you typed 'buy beer'. 'buy 10 beer' would get you\n" +
      "ten beers from the bar, but it takes a little while to\n" +
      "give them all to you.\n");
   return 1;
}
