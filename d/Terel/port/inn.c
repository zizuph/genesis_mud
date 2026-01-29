/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * inn.c
 *
 *  Seafood Inn, originally Hobbiton Bakery.  Modified by Vader
 *  on 7/3/92
 * modified by Mortricia 12/19/92 to suit the port
 */

#include "/d/Terel/include/Terel.h"

inherit STDROOM;
inherit "/lib/trade";

#include <money.h>

#define NUM      sizeof(MONEY_TYPES)

string pay_type, get_type, coin_pay_text, coin_get_text;
int *money_arr;

object inn_keep;

reset_room()
{
   if (!inn_keep) {
       inn_keep = clone_object(PORT_DIR + "monster/inn_keeper");
       inn_keep -> move(TO);
   }
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room() {
   set_short("The Salty Inn");
   set_long("This is the Salty Inn. " +
	    "You are now in a hut where you can order food. " +
	    "They serve only seafood here. " +
	    "There is a menu on a table that you can read.\n");

   add_item(({"table", "tables"}), "They are made of solid oak, and "
            + "are covered by tablecloths.\n");
   add_item(({"menu"}), "@@price_long");

   INSIDE;

   add_exit(PORT_DIR + "road10", "east", 0);

  /* Set up the trading system */
   config_default_trade();
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
   set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */

   reset_room();
}

init()
{
    ::init();
    add_action("do_read","read",0);
    add_action("do_read","study",0);
    add_action("do_buy","buy",0);
    add_action("do_buy","order",0);
}

do_read(str)
{
    NF(capitalize(query_verb()) + " what?\n");
    if (!str || str == "")
	return 0;
    if (str == "pricelist" || str == "list" || str == "prices" ||
	str == "menu") {
	write(price_long());
	return 1;
    }
    return 0;
}

price_long()
{
    return (
	"The menu reads:\n"
	+ "A complete seadog meal ............... 165 cc\n"
	+ "Boiled cod ............................ 70 cc\n"
	+ "Lobster soup .......................... 30 cc\n"
	+ "Fried shrimps ......................... 12 cc\n\n");
}

do_buy(str)
{
    object food;
    string item_name;

    NF("There is no one here to serve you!\n");
    if (!inn_keep || !present(inn_keep)) return 0;

    NF("Buy what?\n");
    if (!str || str == "")
	return 0;

    /*   Check if the player defines what she wants to pay with
     *   and what you would like in return.
     */
    if(sscanf(str, "%s for %s and get %s", item_name, pay_type,
	      get_type) != 3) {
	get_type = "";
   /* Hmmm... Maybe she only wishes to pay with a certain type */
	if (sscanf(str, "%s for %s", item_name, pay_type) != 2) {
	    pay_type = "";
	    item_name = str;
	}
    }

    if (item_name == "meal" || item_name == "seadog meal") {
	if(can_afford(165, "seadog meal")) {
	    food = clone_object(PORT_DIR + "obj/f_meal");
	}
    }
    if (item_name == "cod" || item_name == "boiled cod") {
	if(can_afford(70, "boiled cod")) {
	    food = clone_object(PORT_DIR + "obj/f_cod");
	}
    }
    if (item_name == "soup" || item_name == "lobster soup") {
	if(can_afford(30, "lobster soup")) {
	    food = clone_object(PORT_DIR + "obj/f_soup");
      }
   }
    if (item_name == "shrimps" || item_name == "fried shrimps") {
	if(can_afford(12, "fried shrimps")) {
	    food = clone_object(PORT_DIR + "obj/f_shri");
	}
    }
    if (!food) return 0;
    say(QCTNAME(TP) + " buys the "+food->short()+".\n");
    if(food->move(TP)) {
	write("You cannot carry that much!\n");
	write("You drop the food!\n");
	say(QCTNAME(TP) + " drops the "+food->short()+".\n");
	food->move(TO);
    }
    return 1;
}

/* Test if this_player can afford the price */
can_afford(price, food)
{
    /* Try to take the money */
    if (sizeof(money_arr = pay(price, TP, pay_type, 0, 0, get_type)) == 1) {
	if (money_arr[0] == 2) {
	    tell_room(TO, "The " + inn_keep->query_nonmet_name() + " says: " +
		      "You don't have any " + pay_type +
		      " coins, silly " + TP->query_nonmet_name() + ".\n");
	    return 0;
	}
      if (money_arr[0] == 1) {
         tell_room(TO, "The " + inn_keep->query_nonmet_name() + " says: " +
		   "The " + food + "is a "
		   + "little too expensive to pay for in " + pay_type
		   + " coins, silly " + TP->query_nonmet_name() + ".\n");
         return 0;
     } else {
         tell_room(TO, 
		   "The " + inn_keep->query_nonmet_name() + " says: " +
		   "I don't think so!  You are "
		   + "going to need more money than that, silly "
		   + TP->query_nonmet_name() + ".\n");
         return 0;
     }
    }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You order the " + food + " and pay " + coin_pay_text + ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back.\n");
   return 1;
}
