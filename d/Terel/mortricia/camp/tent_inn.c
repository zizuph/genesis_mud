/*
 *  Gypsy Inn, originally Hobbiton Bakery.  Modified by Vader
 *  on 7/3/92
 * modified by mortricia 10/19/92 to suit the gypsy camp
 */

inherit "/std/room";
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#include "/d/Terel/common/terel_defs.h"

#define NUM      sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define BS(xx)   break_string(xx, 70)
#define BSN(xx)  break_string(xx + "\n", 70)
#define TO       this_object()
#define TP       this_player()
#define CAMP_DIR MORTRICIADIR + "camp/"
#define HAY      MORTRICIADIR + "horses/hay"

string pay_type, get_type, coin_pay_text, coin_get_text;
int *money_arr;

object inn_keep;

reset_room()
{
   if (!inn_keep) {
       inn_keep = clone_object(CAMP_DIR + "inn_keep");
       inn_keep -> move(TO);
   }
}

create_room() {
   set_short("The Gypsy Inn");
   set_long(BSN(
      "You are now in the part of the tent where you can order " +
      "food. " +
      "There is a menu on a table that you can read."
    + " The bar is south from here."
   ));

   add_item(({"table", "tables"}), "They are made of solid oak, and "
            + "are covered by tablecloths.\n");
   add_item(({"menu"}), "@@price_long");

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

   add_exit(CAMP_DIR + "tent_pub", "south", 0);

  /* Set up the trading system */
   config_default_trade();
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
   set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */

   reset_room();
}

init() {
   ::init();
   add_action("do_read","read",0);
   add_action("do_buy","buy",0);
   add_action("do_buy","order",0);
}

do_read(str) {
   if (!str || str == "")
      return 0;
   if (str == "pricelist" || str == "list" || str == "prices" ||
       str == "menu")
   {
      write(price_long());
      return 1;
   }
   return 0;
}

price_long() {
   return (
      "The menu reads:\n"
    + "A complete gypsy meal .................165 cc\n"
    + "Hot and spicy stew .................... 70 cc\n"
    + "Mushroom soup  ........................ 30 cc\n"
    + "Pirogue ............................... 12 cc\n\n"
    + "A bunch of hay ........................ 12 cc\n\n");
}

do_buy(str) {
   object food;
   string item_name;


   if (!inn_keep) return 0;

   if (!str || str == "")
      return 0;

 /*   Check if the player defines what she wants to pay with
  *   and what you would like in return.
 */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
    /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2) {
         pay_type = "";
         item_name = str;
      }
   }

   if (item_name == "meal" || item_name == "gypsy meal") {
      if(can_afford(165, "gypsy meal")) {
          food = clone_object(CAMP_DIR + "g_meal");
          say(QCTNAME(TP) + " buys a gypsy meal.\n");
          if(food->move(TP)) {
            write("You cannot carry that much!\n");
	    write("You drop the food!\n");
            say(QCTNAME(TP) + " drops the meal.\n");
	    food->move(TO);
	  }
      }
      return 1;
   }

    if (item_name == "stew" || item_name == "hot and spicy stew") {
      if(can_afford(70, "hot and spicy stew")) {
         food = clone_object(CAMP_DIR + "g_stew");
         say(QCTNAME(TP) + " buys a bowl of hot and spicy stew.\n");
         if(food->move(TP)) {
            write("You cannot carry that much!\n");
	    write("You drop the food!\n");
            say(QCTNAME(TP) + " drops the stew.\n");
	    food->move(TO);
	 }
      }
      return 1;
   }

   if (item_name == "soup" || item_name == "mushroom soup") {
      if(can_afford(30, "mushroom soup")) {
         food = clone_object(CAMP_DIR + "g_soup");
         say(QCTNAME(TP) + " buys the mushroom soup.\n");
         if(food->move(TP)) {
            write("You cannot carry that much!\n");
	    write("You drop the food!\n");
            say(QCTNAME(TP) + " drops the mushroom soup.\n");
	    food->move(TO);
	 }
      }
      return 1;
   }

   if (item_name == "pirogue") {
      if(can_afford(12, "pirogue")) {
         food = clone_object(CAMP_DIR + "g_piro");
         say(QCTNAME(TP) + " buys a pirogue.\n");
         if(food->move(TP)) {
            write("You cannot carry that much!\n");
	    write("You drop the food!\n");
            say(QCTNAME(TP) + " drops the pirogue.\n");
	    food->move(TO);
	 }
      }
      return 1;
   }
   if (item_name == "hay") {
      if(can_afford(12, "hay")) {
         food = clone_object(HAY);
         say(QCTNAME(TP) + " buys a bunch of hay.\n");
         if(food->move(TP)) {
            write("You cannot carry that much!\n");
	    write("You drop the food!\n");
            say(QCTNAME(TP) + " drops the hay.\n");
	    food->move(TO);
	 }
      }
      return 1;
   }
   return 0;
}

/* Test if this_player can afford the price */
can_afford(price, food) {
 /* Try to take the money */
   if (sizeof(money_arr = pay(price, TP, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 2)
      {
         tell_room(TO, break_string(
	 "The " + inn_keep->query_nonmet_name() + " says: " +
         "You don't have any " + pay_type +
         " coins, silly " + TP->query_nonmet_name() +
         ".\n",70));
         return 0;
      }
      if (money_arr[0] == 1)
      {
         tell_room(TO, break_string(
	    "The " + inn_keep->query_nonmet_name() + " says: " +
            "The " + food + "is a "
          + "little too expensive to pay for in " + pay_type
          + " coins, silly " + TP->query_nonmet_name() +
            ".\n", 70));
         return 0;
      }
      else
      {
         tell_room(TO, break_string(
	    "The " + inn_keep->query_nonmet_name() + " says: " +
            "I don't think so!  You're "
          + "going to need more money than that, silly "
          + TP->query_nonmet_name() + ".\n", 70));
         return 0;
      }
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You order a " + food + " and pay " + coin_pay_text + ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back.\n");
   return 1;
}
