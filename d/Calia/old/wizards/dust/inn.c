/*
 *  Calathin Inn, originally Hobbiton Bakery.  Modified by Vader
 *  on 7/3/92
 */

inherit "/std/room";
inherit "/lib/trade";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

string pay_type, get_type, coin_pay_text, coin_get_text;
int * money_arr;

reset_room()
{
   object inn_keep;

   if(present("jenna"))return;
   inn_keep=clone_object("inn_keep.c");
   inn_keep->move(this_object());
}

create_room() {
   set_short("Calathin Inn");
   set_long(break_string(
      "You are now in the Inn of Calathin.  Never will you find "
    + "a finer example of quality food and service.  There are many "
    + "tables here, where people from all over the world have dined "
    + "on the famous Beaver Stew.  No one really knows exactly what "
    + "ingredient gives it its taste. The entire building is made "
    + "from finely polished and carved wood, with a gothic skylight "
    + "casting shadows of many different colours across the room.  "
      + "There is a menu on a table that you can read.  "
    + "There is also a large chair at one of the tables.  " 
     + "\n", 70));

add_item(({"table", "tables"}), "They are made of solid oak, and "
 + "are covered by tablecloths.\n");
   add_item(({"skylight", "gothic skylight"}), "It depicts several "
    + "angels with musical instruments.\n");
   add_item(({"menu"}), "@@price_long");
   add_cmd_item("menu", "read", "@@price_long");

   add_item(({"chair", "large chair"}), "A rather large chair, " +
              "covered in dust from lack of recent use.  It is " +
              "\nmade from leather, and has the word 'Fatty' " +
              "stitched into the back of it.\n");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   /* add_exit(TOWNDIR + "square2_4", "north", 0); */

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
      "The menu reads:\n\n"
      + "Beaver Stew .................165 Copper coins\n"
    + "Turkey Pie .................. 70 Copper Coins\n"
    + "Squirrel Surprise ........... 30 Copper Coins\n"
    + "Jerky Strip ................. 12 Copper Coins\n"
    + "Donuts    (Sorry, these are reserved for Fatty.)\n\n");
}


do_buy(str) {
   object food;
   string item_name;


   if(!present("jenna"))return 0;

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

   if (item_name == "stew" || item_name == "beaver stew")
   {
      if(can_afford(165, "beaver stew"))
      {
          food = clone_object(STAND_DIR + "b_stew");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " buys a bowl of beaver stew.\n");
      }
      return 1;
   }

    if (item_name == "pie" || item_name == "turkey pie")
   {
      if(can_afford(70, "turkey pie"))
      {
         food = clone_object(STAND_DIR + "t_pie");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " buys a turkey pie.\n");
      }
      return 1;
   }

   if (item_name == "surprise" || item_name == "squirrel surprise")
   {
      if(can_afford(30, "squirrel surprise"))
      {
         food = clone_object(STAND_DIR + "s_surp");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " buys the squirrel surprise.\n");
      }
      return 1;
   }

    if (item_name == "donut" || item_name == "donuts")
   {
      if (this_player()->query_real_name() == "fatty")
      {
         food = clone_object(STAND_DIR + "donut");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
          say(QCTNAME(this_player()) + " buys a donut.\n");
      }
      return 1;
   }
   if (item_name == "jerky" || item_name == "jerky strip")
   {
      if(can_afford(12, "jerky strip"))
      {
         food = clone_object(STAND_DIR + "j_strip");
         if(food->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
          say(QCTNAME(this_player()) + " buys a piece of jerky.\n");
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
         "The long-haired human says: You don't have any " + pay_type
       + " coins, silly " + this_player()->query_nonmet_name()
          + ".\n",70));
         return 0;
      }
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), break_string(
            "The long-haired human says: The " + food + "is a "
          + "little too expensive to pay for in " + pay_type
          + " coins, silly " + this_player()->query_nonmet_name() +
            ".\n", 70));
         return 0;
      }
      else
      {
         tell_room(this_object(), break_string(
            "The long-haired human says: I don't think so!  Your "
          + "going to need more money than that, silly "
          + this_player()->query_nonmet_name() + ".\n", 70));
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
