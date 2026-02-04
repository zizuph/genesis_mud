/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 *  Calathin Inn, originally Hobbiton Bakery.  Modified by Vader
 *  on 7/3/92
  changed agin to Mystic refectory by Mecien
 */

inherit "/std/room";
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#define PATH "/d/Terel/mecien/valley/guild/"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

string pay_type, get_type, coin_pay_text, coin_get_text;
int * money_arr;

reset_room()
{
   object steward;

   if(present("cusuth"))return;
   steward=clone_object(PATH + "steward.c");
   steward->move(this_object());
}

create_room() {
   set_short("Refectory");
   set_long(break_string(
"This vast gilded wooden hall is the refectory of this ancient"
+" shrine, it is here that the mystics nourish themselves. The hall"
 +" is fashioned of beautifully stained wood and gilded into"
+" ornate arches of bronze. Fine gold tapestries line the hall,"
  +" regal in their gleaming splendor. Rows of long tables "
  +" fill the hall, aside each are long benches."
  +" A wooden plaque hangs from the far wall, engraved with "
+"writing."
     + "\n", 70));

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   add_item("tapestries", "They are golden tapestries, they are very\n"
    + "beautiful and hang on most of the walls.\n");
  add_item(({"arches", "ornate arches"}),
   "They are wooden gilded over with bronze, carved with images\n"
   +"of angels and faeries.\n");
add_item(({"rows", "long tables", "tables"}),
  "They are dark stained wood, their surfaces gilded with bronze.\n");
add_item("benches", "Long dark wooden benches.\n");
add_item("plaque", "It is wooden, it has writing upon it.\n");
add_cmd_item("plaque", "read", "@@read");

  add_exit(PATH + "s_hall2", "north", 0);
  /* Set up the trading system */
   config_default_trade();
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
   set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */

   reset_room();

}

read(){

write("PROVISIONS\n" +
  "Order food here through the Steward of the hall. He can\n" +
  "provide you with whatever is listed. All costs are considered\n" +
  "donations. Unfortunately we must insist upon these donations\n" +
  "to keep the refectory open.\n\n" +
  "Herb Broth          10cc\n" +
  "Goat Cheese         30cc\n" +
  "Sweet Porridge      70cc\n" +
  "Unleavened Bread   160cc\n");
return 1;
}
init() {
   ::init();
   add_action("do_buy","order",0);
}

do_buy(str) {
   object food;
   string item_name;


   if(!present("cusuth"))return 0;

   if (!str || str == "")
      return 0;

 /*   Check if the player defines what she wants to pay with
  *   and what you would like in return.
 */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
    /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

   if (item_name == "bread" || item_name == "unleavened bread")
   {
      if(can_afford(160, "unleavened bread"))
      {
          food = clone_object(PATH + "ubread");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
    say(QCTNAME(this_player()) + " receives a loaf of bread from the Steward.\n");
      }
      return 1;
   }

    if (item_name == "porridge" || item_name == "sweet porridge")
   {
      if(can_afford(70, "sweet porridge"))
      {
         food = clone_object(PATH + "porridge");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " receives some porridge from the Steward.\n");
      }
      return 1;
   }

   if (item_name == "cheese" || item_name == "goat cheese")
   {
      if(can_afford(30, "goat cheese"))
      {
         food = clone_object(PATH + "gcheese");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " receives a round of cheese from the Steward.\n");
      }
      return 1;
   }

   if (item_name == "broth" || item_name == "herb broth")
   {
      if(can_afford(10, "herb broth"))
      {
         food = clone_object(PATH + "broth");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
          say(QCTNAME(this_player()) + " receives a cup of broth from the Steward.\n");
      }
      return 1;
   }
   return 0;
}

/* Test if this_player can afford the price */
can_afford(price, food) {
 /* Try to take the money */
   if (sizeof(money_arr = pay(price, this_player(), pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 2)
      {
         tell_room(this_object(), break_string(
   "The Steward says: I cannot take that which you do not "
   +"seem to have. If you have " + pay_type + " you will have "
   +"to show me " + QCTNAME(this_player()) + 
          ".\n",70));
         return 0;
      }
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), break_string(
   "The Steward says: I am sorry " + QCTNAME(this_player()) +
   " but you do not have enough money. I can only provide you "
    +"with food if you have enough money" +
            ".\n", 70));
         return 0;
      }
      else
      {
         tell_room(this_object(), break_string(
   "The Steward says: " + QCTNAME(this_player()) + " you will "
   +"need more money. I cannot give the food away at any less "
    +"than what is listed.\n", 70));
         return 0;
      }
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You order a " + food + " and pay " + coin_pay_text + ".\n");
   if (coin_get_text)
      write("The Steward gives you " + coin_get_text + " back.\n");
   return 1;
}
