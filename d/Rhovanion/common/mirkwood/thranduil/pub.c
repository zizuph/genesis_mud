/*
 *  The pub in Thranduil's Caverns
 */

inherit "/d/Rhovanion/lib/caves.c";
inherit "/lib/pub";
inherit "/lib/trade";

#include "/d/Rhovanion/defs.h"
#include "def.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define MY_PRICES ({ 8, 12, 35, 63 })

create_cave() 
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(2);

  set_long("This is the pub, the place where you can buy liqour of" +
	   " different kinds, the room is full of tables around which" +
	   " a lot of elves sit and drink. At the back of the room" +
	   " you see a counter"+
	   " and behind the counter there is a bartender. You see a " +
	   "pricelist behind the bartender. \n");

  add_item(({"rug","red rug"}),
   "The rug was once beautiful and red, but now it is ugly and grey.\n");

  add_item(({"table","tables","chair","chairs"}),
	   "All the tables and chairs are taken by other elves.\n");

  add_item(({"wallpaper", "green wallpaper", "dark green wallpaper"}),
	   "You notice nothing special about the dark green wallpaper.\n");

  add_item("counter",
	   BS("Above the wooden counter are some candles and a shelf. " +
	      "On the shelf are several brands of liquor. Behind the " +
	      "counter is the barkeeper of this establishment.\n"));
  
  add_item("shelf","On the shelf are several brands of liquor.\n");

  add_item(({"candle","candles"}),"Candles provide some light.\n");

  add_item(({"barkeeper","bartender", "brugan"}), 
	   BS("The barkeeper, Elrohir, is an elf with a big belly. " +
	      "He seldom puts down his wiping cloth, trying to keep " +
	      "the glasses as shiny as possible. Elrohir looks at you, " +
	      "waiting for you to order something.\n"));
  
  add_item(({"pricelist","list","prices"}), "@@price_long");
  
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
  
  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave12","east",0,1);
  
  /* Set up the trading system */
  config_default_trade();

  /* Copper Silver Gold Platinum  */
  set_money_give_out(   ({ 10000,   700,   1,    3 })); /* Max_pay   */
  set_money_give_reduce(({     0,     4,   0,    6 })); /* Threshold */
  
  add_drink(({"ginger ale","ale"}),"ale","ginger",90,1,MY_PRICES[0],
	    "glass of ginger ale", "glasses of ginger ale",
	    BS("The ginger ale has a pink colour and smells like "
	       + "beer mixed with a lot of water.\n"), 0);
  add_drink(({"pint","beer"}),({"pint","beer"}),"prime",110,10,MY_PRICES[1],
	    "pint of prime beer", "pints of prime beer",
	    BS("The prime beer is of prime quality. It was brewn "
               + "in and imported from an Elven village in Grey Havens.\n"),0);
  add_drink("wine", "wine", "red", 70, 25, MY_PRICES[2],
	    "glass of red wine", "glasses of red wine",
	    BS("The sparkling red colour of the wine comes from "
	       + "the riped grapes that the humans of Esgaroth "
	       + "sold to Thranduil..\n"), 0);
  add_drink("whiskey", "whiskey", "dry", 40, 45, MY_PRICES[3],
	    "glass of dry whiskey", "glasses of dry whiskey",
	    BS("The dry whiskey is a bit warm and has a strong "
	       + "smell to it. It was distilled by the humans in "
	       + "Minas Tirith. \n "),0);

  add_food(({ "soup", "elven soup" }), "soup", "elven", 
        50, 10,
        "elven soup", "elven soups", "This is small protion of a soup made by "+
        "elves from Thranduil caves. You don't know what is if made from as "+
        "is quite usual with elven food.\n");
  add_food(({ "quarter of cake", "quarter of herb cake" }),
        "cake", ({"quarter", "of", "herb"}), 
        75, 15,
        "quarter of herb cake", "quarters of herb cake", 
        "This is quarter of a cake. As the name suggests it is made mainly "+
        "from herbs but exact recepy is the secret of the elves from "+
        "Thranduil caves. You may never find it out but you can be "+
        "sure that it will refresh you on your long journeys.\n");
  add_food(({ "half of cake", "half of herb cake" }),
        "cake", ({"half", "of", "herb"}),
        150, 40,
        "half of herb cake", "halves of herb cake", 
        "This is half of a cake. As the name suggests it is made mainly "+
        "from herbs but exact recepy is the secret of the elves from "+
        "Thranduil caves. You may never find it out but you can be "+
        "sure that it will refresh you on your long journeys.\n");
  add_food(({ "cake", "whole cake", "whole herb cake" }),
        "cake", ({"whole", "herb"}),
        300, 155,
        "herb cake", "herb cakes", 
        "As the name suggests this cake is made mainly "+
        "from herbs but exact recepy is the secret of the elves from "+
        "Thranduil caves. You may never find it out but you can be "+
        "sure that it will refresh you on your long journeys.\n");
}

init() 
{
  ::init();
  init_pub();
  add_action("do_read","read",0);
}
     
do_read(str) 
{
  if (!str || str == "")
    return 0;
  if (str == "pricelist" || str == "list" || str == "prices")
    {
      write(price_long());
      return 1;
    }
  return 0;
}

price_long() 
{
  return ("The pricelist reads:\n\n"
	  + "   Ginger ale      ...  " + MY_PRICES[0] + " copper coins\n"
	  + "   Beer            ...  " + MY_PRICES[1] + " copper coins\n"
	  + "   Wine            ...  " + MY_PRICES[2] + " copper coins\n"
          + "   Whiskey         ...  " + MY_PRICES[3] + " copper coins\n\n"
          + "   Elven soup      ...  " + 10 + " copper coins\n"
          + "   Herb cake       ...  " + 155 + " copper coins\n"
          + "   Half of cake    ...  " + 40 + " copper coins\n"
          + "   Quarter of cake ...  " + 15 + " copper coins\n\n");
}

