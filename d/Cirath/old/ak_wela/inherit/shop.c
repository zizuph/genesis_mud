/*
 * The herb shop in the city of Ak Wela, modified by Astro
 * from the Hin Warrior herb shop (thanks Tricky, Dunstable, etc.)
 * Astro, Feb. 1995
 */

/*
 *  TO DO:
 *    - Perhaps the shop owner should be made as a mobile
 */

inherit "/std/room";
inherit "/lib/trade";

#include "/d/Cirath/common/defs.h"
#include "/sys/money.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

// Where the items are stored.
#define STORE_ROOM (AK_WELA_DIR + "herbshop_store")
// Maximum price the owner will pay out.
#define MAX_PAY 1000
// Minimum price players will be able to pay.
#define MIN_SELL 10

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

object item_arr, weapon_arr, armour_arr, herb_arr, to;

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
   set_short("Herbstore");
   set_long(
      "You have stumbled into a dusty, dark shop. Potions line the wall "
    + "and funny coloured herbs hang from the ceiling. The owner of "
    + "the store has written down all items on a pricelist, together "
    + "with their price. If you like something, feel free to buy it. "
    + "A small note has been pinned to the wall.\n");

   add_item(({"small note", "note"}), "@@note_long");

   add_item(({"list","pricelist","prices"}), "@@price_long");

   add_item(({"item","items", "potions", "herbs"}), 
      "There are far too many items lying around to single one out. You "
    + "should better take a look at the pricelist, to get an idea of what "
    + "useful stuff you can buy here.\n");

   add_item(({"owner",}), 
      "The owner of the store is watching you closely, so you do not get "
    + "the chance to steal anything. Besides that, he leaves you on your "
    + "own to check out the stuff that is lying around.\n");

   add_exit(AK_WELA_DIR + "brdwlk2", "east", 0);
   add_exit(STORE_ROOM, "west", "@@wiz_check");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   config_default_trade();  /* Set up the trading system */
   set_money_give_max(100000); /* Else things go wrong with "sell all" */
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
   set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */

   /* Force STORE_ROOM to be loaded */
   (STORE_ROOM)->short();
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
init()
{
   ::init();   /* You MUST do this in a room-init */
   add_action("do_buy","buy",0);
   add_action("do_read","read",0);
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
wiz_check()
{
   seteuid(geteuid(this_object()));
   if (this_player()->query_wiz_level())
      return 0;
   write("The owner of the store keeps you from going there.\n");
   say("The owner of the store blocks " + QCTNAME(this_player()) + ".\n");
   return 1;
}

/*
 * Function name:   do_buy
 * Arguments:       string the_item
 * Description:     Try to let the player buy the_item
 *                  Description of the string the_item:
 *
 *                     item/itemnum [for <money_type> [and get <money_type>]]
 *
 *                  Examples:                  
 *                      buy sword for silver and get copper
 *                      buy sword for platinum
 *
 * Returns:         Always 1
 */
do_buy(str)
{
   object item, item2, tp, *obs;
   int m_s, indx, int_str, value, item_nr;
   int * money_arr;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text;

   tp = this_player();
   if(!str || str =="")
   {
      tell_room(this_object(), break_string(
         "The owner says: Tough to make up your mind eh, "
       + tp->query_nonmet_name() + "?\n",70));
      return 1;
   }

   /* Force STORE_ROOM to load */
   (STORE_ROOM)->short();

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

   if (pay_type != "")
   {
      if (member_array(pay_type, MONEY_TYPES) < 0)
      {
         tell_room(this_object(), break_string(
            "The owner says: I don't accept those " + pay_type + " coins, "
          + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }
   }

   if (get_type != "")
   {
      if (member_array(get_type, MONEY_TYPES) < 0)
      {
         tell_room(this_object(), break_string(
            "The owner says: I don't have any " + get_type
          + " coins, " + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }
   }

   /* Did the player give an item-number? */
   if (sscanf(item_name, "%d", int_str))
   {
      item_arr = all_inventory(find_object(STORE_ROOM));
      if (!sizeof(item_arr))
      {
         tell_room(this_object(), break_string(
            "The owner says: I am afraid that is all sold out, "
          + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }

      /* Sort the items in arrays */
      to = this_object();
      herb_arr = filter(item_arr,"herb_filter", to);

      m_s = sizeof(herb_arr);

      if (int_str-1 < 0 || int_str-1 >= m_s)
      {
         tell_room(this_object(), break_string(
            "The owner says: I don't have that many items, "
          + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }
      else
      {
         item = herb_arr[int_str-1];
      }
   }
   else  /* The player gave an item-string, try to locate it. */
   {
      if(!(item = present(item_name, find_object(STORE_ROOM))))
      {
         tell_room(this_object(), break_string(
            "The owner says: I don't have such " + item_name + " here, "
          + tp->query_nonmet_name() + "...\n",70));
         return 1;
      }
   }

   /* Enforce a minimum value of an item */
   value = sell_value(item->query_herb_value());

   if (value == 0)
      value = item->query_prop(OBJ_I_VALUE);

   if (value < MIN_SELL)
      value = MIN_SELL;

   /* Try to take the money */
   if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), break_string(
            "The owner says: I think that " + item->short() + " is a bit "
          + "more expensive, " + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }
      if (money_arr[0] == 2)
      {
         tell_room(this_object(), break_string(
            "The owner says: You do not have any " + pay_type + " coins, "
          + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }
      else
      {
         tell_room(this_object(), break_string(
            "The owner says: I think that " + item->short() + " is a bit "
          + "too expensive for you, " + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }
   }

   /* Okay, the item is paid for, now give one of it to the player */
   seteuid(getuid());
   item_nr = item->num_heap();

   /* If it consists of more than one, make a clone and continue with that */
   if (item_nr > 1)
   {
      item2 = clone_object(MASTER_OB(item));	/* Make another item to give */
      item2->set_heap_size(1);
      item->set_heap_size(item_nr - 1);		/* Decrease the number left */
      item = item2;
   }

   if(item->move(tp))
   {
      tell_room(this_object(), break_string(
         "The owner says: You cannot carry that " + item->short() + ", "
       + tp->query_nonmet_name() + ".\n",70));
      tell_room(this_object(),
         "The owner says: I will put it on the ground for you.\n"
       + "The owner drops the " + item->short() + ".\n");
      item->move(this_object());
      return 1;
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   say(QCTNAME(tp) + " buys "    + item->short() + ".\n");
   write("You buy " + item->short() + " and pay " +coin_pay_text+ ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " in return.\n");
   return 1;
}


/*
 * Function name:   do_read
 * Arguments:       string list_name
 * Description:     Provide an alias for "exa pricelist"
 * Returns:         0 if not recognised
 *                  1 otherwise
 */
do_read(str)
{
   if (str == "pricelist" || str == "list" || str == "prices") {
      write(price_long());
      return 1;
   }
   if (str == "note" || str == "small note") {
      write(note_long());
      return 1;
   }
   return 0;
}

note_long()
{
   return break_string(
      "If you want to sell herbs, find Lothmir, the herb-master of "
    + "the Rangers, or Tobold Hornblower, a local farmer. " 
    + "They are said to know a great deal about herbs "
    + "and plants, and are eager to trade them.\n", 70);
}
/*
 * Function name:   price_long
 * Description:     Give a list of all objects in the STORE_ROOM.
 *                  The items on the list are categorized and numbered.
 * Returns:         A string with the above described list.
 */
price_long()
{
   int i, value, previous;
   string the_long, tmp, fill_str, val_str;

   /* This is a VBFC function, so make sure our euid is set */
   seteuid(getuid());

   /* Force STORE_ROOM to be loaded */
   (STORE_ROOM)->short();
   item_arr = all_inventory(find_object(STORE_ROOM));
   if (!sizeof(item_arr))
      return "The drugstore is empty at the moment.\n";

   to = this_object();
   herb_arr = filter(item_arr,"herb_filter", to);

   fill_str = "                                                       ";
   previous = 1;

   the_long = "\n       ----- Herbs for sale ------\n";   
   if (!sizeof(herb_arr))
      the_long += "   None\n";
   else
   {
      for(i=0; i<sizeof(herb_arr); i++) {
         /* Align the numbers nicely */
         if ((i + previous) < 10)
            tmp = "   ";
         else if ((i + previous) < 100)
            tmp = "  ";
         else
            tmp = " ";

         tmp += ((i + previous) + ":  ");
         tmp +=  herb_arr[i]->short();
         if (strlen(tmp) < 40)
            tmp += extract(fill_str,strlen(tmp),40);
         tmp += "   ";

         /* Enforce a minimum value of an item */
         value = sell_value(herb_arr[i]->query_herb_value());

         if (value == 0)
            value = herb_arr[i]->query_prop(OBJ_I_VALUE);

         if (value < MIN_SELL)
               value = MIN_SELL;

         val_str = sprintf("%5d", value);
         tmp += (val_str +" coppers a piece\n");
         the_long += tmp;
      }
   }
   the_long += "\n";
   return the_long;
}


sell_value(old_value)
{
   string guild;
   guild = this_player()->query_guild_name_lay();

   if (guild == "Shire")
      return 2*old_value;
   return 4*old_value;
}

herb_filter(obj)
{
   return (function_exists("create_object", obj) == "/std/herb"
	|| obj->query_is_tobacco());
}
