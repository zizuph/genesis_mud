
/*  
    The Gelan Grocery store 
    Some of this is based on Tricky's Hobitton bakery.

    coder(s):   Maniac

    history:     9.1.95      Created                            Maniac

    purpose:	buy special fruit and veg items here 
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

string pay_type, get_type, coin_pay_text, coin_get_text;
int * money_arr;
object keeper;

mapping prices = ([ "melon": 162,
                    "apple": 76,
                    "celery": 76,
                    "beetroot": 100,
                    "broccoli": 252,
                    "banana": 134,
                    "orange": 101,
                 ]); 

mapping item_path = ([ "melon": GELAN_OBJECTS + "melon",
                       "apple": GELAN_OBJECTS + "apple",
                       "celery": GELAN_OBJECTS + "celery",
                       "beetroot": GELAN_OBJECTS + "beetroot",
                       "broccoli": GELAN_OBJECTS + "broccoli",
                       "banana": GELAN_OBJECTS + "banana",
                       "orange": GELAN_OBJECTS + "orange",
                    ]);

int can_afford(int price, object food);

public void
create_gelan_room() {
   set_short("The Tomati Empire Grocery");
   set_long(
      "You stand in a haven of healthy eating that is known as the " +
      "Tomati Empire, the mother of all grocery shops. " +
      "Most of the space in here is taken up by huge " +
      "baskets full of various fruits and vegetables. Only " +
      "the best of everything for this shop: anything that " + 
      "is not perfectly ripe or in any way sub-standard is " +
      "thrown out for use in the pillory. Although rustic, this " +
      "place is a delight to be in. Its wares are lovingly " +
      "arranged all around you, with the multitude of fresh fruit " +
      "aromas making you feel quite hungry. On one wall is a " +
      "pricelist.\n");

   add_item(({"pricelist","list","prices"}), "@@price_long");
   add_cmd_item(({"pricelist","list","prices"}), "read", "@@price_long");

   add_item(({"fruits", "vegetables", "fruit", "vegetable"}),
             "There is a large selection " +
             "of fruit and vegetables on display here in numerous large " +
             "baskets all around the shop. You notice " +
             "that the condition of all the food is perfect and it all " +
             "appears to have been harvested only recently. The " +
             "pricelist on the wall gives details of what is " +
             "available here and for what price.\n"); 

   add_item(({"basket", "baskets", "huge baskets"}), "The huge baskets " +
            "are arranged all around the shop, each one containing a " +
            "different kind of fruit or vegetable, piled up carefully " +
            "to avoid bruising.\n");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   add_exit(GELAN_ROOMS + "square_corner_sw","north",0);
   add_exit(GELAN_ROOMS + "square_southend_w","east",0);

  /* Set up the trading system */
   config_default_trade();

   reset_room();
}



string
price_long() 
{
   string *indices, str;
   int i, j;

   str = "The pricelist reads:\n\n";
  
   indices = m_indexes(prices);
   for (i = 0; i < sizeof(indices); i++) {
      str += "   " + capitalize(indices[i]); 
      for (j = 0; j < (20 - strlen(indices[i])); j++)
          str += " ";
      str +=  "...  " + prices[indices[i]] + " cc.\n";
   }
   str += "\n";
 
   return str;
}


reset_room()
{
  if (!keeper) fix_keeper();
}

fix_keeper()
{
  keeper = clone_object(GELAN_MONSTERS + "patati");
  keeper->move(TO);
  tell_room(this_object(), QCTNAME(keeper) + " arrives.\n");
}



check_keeper()
{
  if (present("shopkeeper")) return 1;
  else return 0;
}


int
no_keeper()
{
  write("There is no shopkeeper here, so you can't do that!\n");
  return 1;
}


/* 
 * Buy a particular item from the shop 
 */
int
buy_item(string arg)
{
   object food;
   int n, p ;
   string itp, item_name, *el; 

   notify_fail("Buy what?\n"); 
   if (!stringp(arg) || !strlen(arg)) { 
       return 0;
   } 

   int isProduceName = 0;
   item_name = explode(arg, " ")[-1];
   foreach (string produce : m_indices(prices))
   {
       if (produce == item_name)
       {
           isProduceName = 1;
           break;
       }
       else if (LANG_PWORD(produce) == item_name)
       {
           isProduceName = 1;
           item_name = produce;
           break;
       }
   }
   if (!isProduceName)
   {
       notify_fail("We don't stock food of that name here.\n");
       return 0;
   }

   string numProduce = implode(explode(arg, " ")[..-2], " ");
   if (!strlen(numProduce))
   {
       n = 1;
   }
   else
   {
       if (parse_command(numProduce, this_object(), " %d ", n) == 0)
       {
           n = LANG_WORD2NUM(numProduce);
       }
       if (n <= 0)
       {
           notify_fail("How many do you want to buy?\n");
           return 0;
       }
   }
   
   if (n > 50)
   { 
       notify_fail("That is too many in one go!\n"); 
       return 0;
   } 
   itp = item_path[item_name]; 
   p = prices[item_name]; 
   if (!p || !itp)
   {
        notify_fail("We don't stock food of that name here.\n"); 
        return 0;
   } 
   p = p * n; 

   seteuid(getuid());
   food = clone_object(itp);
   food->set_heap_size(n); 

   if (can_afford(p, food))
   {
       tell_room(this_object(),
                 QCTNAME(this_player()) + " buys " + LANG_ASHORT(food) + ".\n",
                 this_player());
       if (food->move(this_player()))
       {
           keeper->command("say You can't carry " + LANG_ASHORT(food) +  
                           ", so I'll just put your goods down.\n");
           food->move(environment(this_player()));
           return 1;
       }
   }
   return 1;
}


/* Player attempts a buy command in the shop */
int
do_buy(string str)
{
   string item_name;

   if (!check_keeper()) return no_keeper();

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
         item_name = lower_case(str);
      }
   }

   return buy_item(item_name);
}



/* Test if this_player can afford the price */
int
can_afford(int price, object food) {
 /* Try to take the money */
   if (sizeof(money_arr = 
       pay(price, this_player(), pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 2)
      {
         keeper->command("say "   
          + " You don't have any " + pay_type
          + " coins, honored " + this_player()->query_nonmet_name()
          + ".\n");
         return 0;
      }
      if (money_arr[0] == 1)
      {
         keeper->command("say "
          + "I think " + LANG_ASHORT(food) + " is too "
          + "expensive to pay for in " + pay_type + " coins only, honored "
          + this_player()->query_nonmet_name() + ".\n");
         return 0;
      }
      else
      {
          keeper->command("say " 
          + "I'm afraid " + LANG_ASHORT(food) + " is a bit "
          + "above your budget, honored " 
          + this_player()->query_nonmet_name()
          + ".\n");
         return 0;
      }
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You order " + LANG_ASHORT(food) + 
         " and pay " + coin_pay_text + ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back.\n");
   return 1;
}

void
init() 
{
   ::init();
   add_action(do_buy,"buy");
}

