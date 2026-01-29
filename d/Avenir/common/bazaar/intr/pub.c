// file name: bazaar/intr/pub.c
// creator(s): Ilyian May 1995
// last update:  Lilith, May 2022: added minstrel performance location
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/room";
inherit "/lib/pub";
inherit "/lib/trade";

#include "../bazaar.h";
#include "/sys/money.h"

static object waitress;

#define MY_PRICES ({11,13,71,189})

create_room() {
   set_short("Icky Bod's Pub and Club");
   set_long(
        "You stand in the centre of Icky Bod's, a local pub and "+
        "dance club. In the front of the room there is a bar with "+
        "a menu posted on the wall "+
        "beside it. Around the bar there are some stools for the "+
        "regular patrons, and the rest of the bar is "+
        "filled with tables and chairs. You can hear music coming "+
        "from the room to the north.\n");

   AI("stools", "Small wooden stools that don't appear entirely stable.\n");
   AI("bar", "A dark coloured bar marred with many scratches.\n");
   AI("menu", "It has some words written on it.\n");
   AI("chairs", "Small wooden chairs full covered with cracks and marks.\n");
   AI("tables", "Looking at the tables, you see a great amount "+
            "of carvings on them.\n");
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.
    add_prop("_minstrel_performance_location", ({ "icky bod's", 2 }) );

   AE(EXTR+"str8","west", 0);
   AE(INTR+"gogo", "north", 0);

   config_default_trade();
   set_money_give_out(({10000,700,1,3}));
   set_money_give_reduce(({0,4,0,6}));

   add_drink("water","water","fresh", 90, 0, MY_PRICES[0],
             "glass of water", "glasses of water",
             "It is simply water, sparkling fresh and clear.\n",0);

   add_drink(({"pint","beer"}),({"pint","beer"}),"strong",110,33,MY_PRICES[1],
             "pint of strong beer", "pints of strong beer",
             "The prime beer is of prime quality. It was brewn "
             +"in and imported from an Elven village in the Grey "
             +"Havens.\n", 0);

   add_drink("wine", "wine", "red", 70, 40, MY_PRICES[2],
             "glass of red wine", "glasses of red wine",
             "This deep and dark red wine is pressed from "
            +"the ripened grapes that were harvested in the "
            +"vinyards of Argos.\n", 0);

   add_drink("cognac", "cognac", "dark",10, 60, MY_PRICES[3],
             "glass of cognac", "glasses of cognac",
             "The dark cognac is a bit warm and has a strong "
            +"smell to it.\n",0);

    reset_room();
}

init() {
   ::init();
   init_pub();
   add_action("do_read","read",0);
}


do_read(str) {
   if (!str || str == "")
      return 0;
   if (str == "pricelist" || str == "list" || str == "menu")
   {
      write(price_long());
      return 1;
   }
   return 0;
}

price_long() 
{
   return (
      "The pricelist reads:\n\n"
    + "   Fresh Water         -   " + MY_PRICES[0] + " copper coins\n"
    + "   Thick Beer          -   " + MY_PRICES[1] + " copper coins\n"
    + "   Dark Red Wine       -   " + MY_PRICES[2] + " copper coins\n"
    + "   Cognac              -   " + MY_PRICES[3] + " copper coins\n");
}

reset_room()
{
  if (!waitress)
   {
      waitress = clone_object(NPC + "waitress");
      waitress->arm_me();
      waitress->move_living("M", this_object());
    }
}

