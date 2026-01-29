
/*  The Gelan Bakery, a modification of 
 *  the Minas Tirith bakery (thanks Elessar), which was a modification of
 *  the Hobbiton bakery (thanks Tricky)
 *  This is where the gopheroo quest of Gelan is finished. 

    coder(s):   Maniac

    history:  16/12/2001    added code for gingerbread quest  Uhclem
                 6/4/98     added breadsticks                 Uhclem
                 6/6/97     won't serve town enemies          Maniac
                 31.8.96    items added                       Maniac
                 24.1.95    Modified on quest change          Maniac
                 12.9.94    description slightly altered      Maniac
                    6.94    coded                             Maniac

    purpose:	buy food here
    exits:      west to the square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include GUARD_INCLUDE
#include "/d/Calia/yuleware/defs.h"             // for gingerbread quest

inherit GELAN_BASE_ROOM;
inherit "/lib/trade";

#define MY_PRICES ({ 7, 22, 43, 72, 144, 155, 272 })
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

string pay_type, get_type, coin_pay_text, coin_get_text;
int * money_arr;
object keeper;

int can_afford(int price, string food);

public void
create_gelan_room() {
   set_short("The McCroissant Bakery");
   set_long(
      "You are in the McCroissant bakery of Gelan.  It looks " +
      "rather homely and colourful. Smells such as mixed " +
      "spice, ground sesame seeds and nearly-baked sweet pastry are in " +
      "the air. Many glass display shelves hold the mouthwatering wares " +
      "of this attractive little shop, where you can buy many kinds " +
      "of fresh baked food, from the dainty to the very filling. " +
      "In one corner of the room is a hutch. " +
      "There is a pricelist on the wall for you to read.\n");

   add_item(({"pricelist","list","prices"}), "@@price_long");

   add_item(({"shelf", "shelves", "display shelves", "glass shelves"}), 
             "To see what is available, please examine the pricelist.\n"); 

   add_item("hutch", "@@hutch_des");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   add_exit(GELAN_ROOMS + "square_southend_e","west",0);

  /* Set up the trading system */
   config_default_trade();

                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,   20,    3 })); /* Max_pay   */
   set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */

   set_alarm(1.0, 0.0, reset_room);
}


string
hutch_des()
{
     string str = 
         "It looks like a gopheroo hutch. There is no gopheroo " +
         "in it though, perhaps it somehow got out.\n";
    return str;
}

string
price_long() 
{
   return (
      "The pricelist reads:\n\n"
    + "   Half dozen breadsticks ..   " + MY_PRICES[0] + " cc.\n"
    + "   Custard pie .............   " + MY_PRICES[1] + " cc.\n"
    + "   Shortcake finger ........   " + MY_PRICES[2] + " cc.\n"
    + "   Croissant ...............   " + MY_PRICES[3] + " cc.\n"
    + "   Mint chocolate puff......   " + MY_PRICES[4] + " cc.\n"
    + "   Sesame bread ............   " + MY_PRICES[5] + " cc.\n"
    + "   Fat bastard cake ........   " + MY_PRICES[6] + " cc.\n"
    + "   A close look at some of these items is recommended.\n\n");
}


int
do_read(string str) 
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


void
fix_keeper()
{
    keeper = clone_object(GELAN_MONSTERS + "baker");
    keeper->move_living("into the shop", TO);
}


void
reset_room()
{
    object gingerbread_dispenser = present("_calia_gingerbread_dispenser", TO);
    string *datetext = explode(ctime(time()), " ");

    if (!keeper) fix_keeper();

    /*
     *  The following code puts an object for the gingerbread quest
     *  into this room from December 17 to January 16 each year.
     */

    if (strlen(datetext[2]) == 1)
    {
        datetext[2] = "0" + datetext[2];
    }

    if (((datetext[1] == "Dec" && datetext[2] >= "17") ||
        (datetext[1] == "Jan" && datetext[2] <= "16")) &&
        !gingerbread_dispenser)
    {
        gingerbread_dispenser = clone_object(GINGERBREAD_DISPENSER);
        gingerbread_dispenser->move(TO);
    }

    if (gingerbread_dispenser)
    {
        gingerbread_dispenser->reset_dispenser();
    }

    if (datetext[1] == "Dec" && !gingerbread_dispenser)
    {
        keeper->add_ask(({"yule", "yule season"}),
            "say Yule season is coming; it won't be long before" +
            " I start making gingerbread cookies!", 1);
        keeper->add_ask(({"cookies", "cookie", "gingerbread"}),
            "say Sorry, I haven't started making gingerbread" +
            " cookies yet, but you can be sure I'll save one" +
            " for you when I do!", 1);
    }

    if (datetext[1] == "Jan" && !gingerbread_dispenser)
    {
        keeper->add_ask(({"yule", "yule season"}),
            "say Yule season ended a couple of weeks ago," +
            " but it's nice to see that the spirit lives on!", 1);
        keeper->add_ask(({"cookies", "cookie", "gingerbread"}),
            "say Sorry, I've run out of gingerbread cookies." +
            " I won't be making them again until next" +
            " yule season.", 1);
    }

    /*  End of gingerbread quest addition.  */

}


int
check_keeper()
{
  if (keeper && present(keeper, this_object())) return 1;
  else return 0;
}


int
no_keeper()
{
  write("There is no shopkeeper here, so you can't do that!\n");
  return 1;
}



int
do_buy(string str)
{
   object food;
   string item_name;

   if (!check_keeper()) return no_keeper();

   if (this_player()->query_prop(ATTACKED_GELAN)) { 
       keeper->command("say to " + this_player()->query_real_name() + 
                       " I'd prefer not to have your custom thank you!"); 
       return 1; 
   } 

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

   if (item_name == "breadsticks" || item_name == "half dozen breadsticks")
   {
      if(can_afford(MY_PRICES[0], "half dozen breadsticks"))
      {
         tell_room(this_object(),
             QCTNAME(this_player()) + " buys some breadsticks.\n", 
                                                 this_player());
         food = clone_object(GELAN_OBJECTS + "breadsticks");
         if(food->move(this_player()))
         {
            keeper->command("say You can't carry those breadsticks, " + 
                          "so I'll just put them down.\n");
	    food->move(environment(this_player()));
            return 1;
         }
      }
      return 1;
   }

   if (item_name == "pie" || item_name == "custard pie")
   {
      if(can_afford(MY_PRICES[1], "custard pie"))
      {
         tell_room(this_object(),
             QCTNAME(this_player()) + " buys a custard pie.\n", 
                                                 this_player());
         food = clone_object(GELAN_OBJECTS + "custard_pie");
         if(food->move(this_player()))
         {
            keeper->command("say You can't carry that pie, " + 
                          "so I'll just put it down.\n");
	    food->move(environment(this_player()));
            return 1;
         }
      }
      return 1;
   }

   if (item_name == "finger" || item_name == "shortcake" ||
       item_name == "shortcake finger")
   {
      if(can_afford(MY_PRICES[2], "shortcake finger"))
      {
         tell_room(this_object(),
             QCTNAME(this_player()) + " buys a shortcake finger.\n", 
                                                 this_player());
         food = clone_object(GELAN_OBJECTS + "shortcake");
         if(food->move(this_player()))
         {
            keeper->command("say You cannot carry that shortcake " +
                            "finger, so I'll just put it down.\n");
	    food->move(environment(this_player()));
            return 1;
         }
      }
      return 1;
   }

   if (item_name == "croissant")
   {
      if(can_afford(MY_PRICES[3], "croissant"))
      {
         tell_room(this_object(),
             QCTNAME(this_player()) + " buys a croissant.\n", 
                                                 this_player());
         food = clone_object(GELAN_OBJECTS + "croissant");
         if(food->move(this_player()))
         {
            keeper->command("say You cannot carry that croissant, " +
                            "so I'll just put it down.\n");
	    food->move(environment(this_player()));
            return 1;
         }
      }
      return 1;
   }

   if (item_name == "mint" || item_name == "mint puff" ||
       item_name == "mint chocolate puff" || item_name == "chocolate puff" ||
	   item_name == "puff")
   {
      if(can_afford(MY_PRICES[4], "mint chocolate puff"))
      {
         tell_room(this_object(),
             QCTNAME(this_player()) + " buys a mint puff.\n", 
                                                 this_player());
         food = clone_object(GELAN_OBJECTS + "mint");
         if(food->move(this_player()))
         {
            keeper->command("say You cannot carry that mint puff, " +
                            "so I'll just put it down.\n");
	    food->move(environment(this_player()));
            return 1;
         }
      }
      return 1;
   }
   if (item_name == "bread" || item_name == "sesame bread")
   {
      if(can_afford(MY_PRICES[5], "sesame bread"))
      {
         tell_room(this_object(),
             QCTNAME(this_player()) + " buys a loaf of sesame bread.\n", 
                                                 this_player());
         food = clone_object(GELAN_OBJECTS + "sesame_bread");
         if(food->move(this_player()))
         {
            keeper->command("say You cannot carry that bread, " +
                            "so I'll just put it down.\n");
	    food->move(environment(this_player()));
            return 1;
         }
      }
      return 1;
   }

   if (item_name == "cake" || item_name == "fat cake" ||
       item_name == "fat bastard cake" || item_name == "bastard cake")
   {
      if(can_afford(MY_PRICES[6], "fat bastard cake"))
      {
         tell_room(this_object(),
             QCTNAME(this_player()) + " buys a fat bastard cake.\n", 
                                                 this_player());
         food = clone_object(GELAN_OBJECTS + "fat_cake");
         if(food->move(this_player()))
         {
            keeper->command("say You cannot carry that fat bastard cake" +
                            ", so I'll just put it down.\n");
	    food->move(environment(this_player()));
            return 1;
         }
      }
      return 1;
   }

   return 0;
}



/* Test if this_player can afford the price */
int
can_afford(int price, string food) {
 /* Try to take the money */
   if (sizeof(money_arr = pay(price, this_player(), pay_type, 0, 0, get_type)) == 1)
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
          + "I think that " + food + " is too "
          + "expensive to pay for in " + pay_type + " coins only, honored "
          + this_player()->query_nonmet_name() + ".\n");
         return 0;
      }
      else
      {
          keeper->command("say " 
          + "I'm afraid that " + food + " is a bit "
          + "above your budget, honored " 
          + this_player()->query_nonmet_name()
          + ".\n");
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


void
init() {
   ::init();
   add_action(do_read,"read");
   add_action(do_buy,"buy");
}

