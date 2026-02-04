/*
 *  The Hobbiton bakery
 */

inherit "/std/room";
inherit "/lib/trade";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define MY_PRICES ({ 5, 12, 6, 9 })
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

string pay_type, get_type, coin_pay_text, coin_get_text;
int * money_arr;

create_room() {
   set_short("Bakery");
   set_long(break_string(
      "You have entered the local bakery. The smell of fresh bread "
    + "lingers in the air. You see all kinds of delicious cakes, "
    + "bread and pies inside the glass counter. A friendly hobbit "
    + "is behind the counter, ready to serve you if you feel like "
    + "ordering something. Behind her, on the wall, is a pricelist.\n",70));

   add_item(({"counter","glass counter"}), break_string(
      "Inside the glass counter you see lots of different kinds of bread, "
    + "cakes and various kinds of pies. Water starts to run in your mouth "
    + "if you look at them for too long.\n",70));

   add_item(({"bread","breads"}), break_string(
      "The bread was freshly baked this morning. The whole bakery smells "
    + "like the bread, which looks quite tasty.\n",70));

   add_item(({"cake","cakes"}), break_string(
      "There are many cakes displayed here, varying from small to big. "
    + "Boy, would you love to put your teeth in one of those!\n",70));

   add_item(({"pie","pies"}), break_string(
      "The big pie in the middle looks like it is the most tasty one "
    + "of all. It is an apple pie, just like your grandmother used to "
    + "bake them when you were a little kid.\n",70));

   add_item(({"pricelist","list","prices"}), "@@price_long");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   add_exit(STAND_DIR + "bw_road4", "south", 0);

  /* Set up the trading system */
   config_default_trade();
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
   set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */
}

init() {
   ::init();
   add_action("do_read","read",0);
   add_action("do_buy","buy",0);
}

do_read(str) {
   if (!str || str == "")
      return 0;
   if (str == "pricelist" || str == "list" || str == "prices")
   {
      write(price_long());
      return 1;
   }
   return 0;
}

price_long() {
   return (
      "The pricelist reads:\n\n"
    + "   Apple pie       ...   " + MY_PRICES[0] + " copper coins\n"
    + "   Strawberry cake ...   " + MY_PRICES[1] + " copper coins\n"
    + "   White bread     ...   " + MY_PRICES[2] + " copper coins\n"
    + "   Brown bread     ...   " + MY_PRICES[3] + " copper coins\n\n");
}


do_buy(str) {
   object food;
   string item_name;

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

   if (item_name == "pie" || item_name == "apple pie")
   {
      if(can_afford(MY_PRICES[0], "apple pie"))
      {
         food = clone_object(STAND_DIR + "f_pie");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " buys a piece of apple pie.\n");
      }
      return 1;
   }

   if (item_name == "cake" || item_name == "strawberry cake")
   {
      if(can_afford(MY_PRICES[1], "strawberry cake"))
      {
         food = clone_object(STAND_DIR + "f_cake");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " buys strawberry cake.\n");
      }
      return 1;
   }

   if (item_name == "bread")
   {
      write("Which kind of bread: white or brown?\n");
      return 1;
   }

   if (item_name == "white" || item_name == "white bread")
   {
      if(can_afford(MY_PRICES[2], "white bread"))
      {
         food = clone_object(STAND_DIR + "f_w_bread");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " buys a piece of white bread.\n");
      }
      return 1;
   }

   if (item_name == "brown" || item_name == "brown bread")
   {
      if(can_afford(MY_PRICES[3], "brown bread"))
      {
         food = clone_object(STAND_DIR + "f_b_bread");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " buys a piece of brown bread.\n");
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
            "The friendly hobbit says: You have not got any " + pay_type
          + " coins, my dear " + this_player()->query_nonmet_name()
          + ".\n",70));
         return 0;
      }
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), break_string(
            "The friendly hobbit says: I think that " + food + " is too "
          + "expensive to pay for in " + pay_type + " coins only, my dear "
          + this_player()->query_nonmet_name() + ".\n",70));
         return 0;
      }
      else
      {
         tell_room(this_object(), break_string(
            "The friendly hobbit says: I think that " + food + " is a bit "
          + "above your budget, my dear " + this_player()->query_nonmet_name()
          + ".\n",70));
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
