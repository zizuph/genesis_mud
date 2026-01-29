/*
   Wayreth.

   shop.c
   ------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/06/07
   By ...........: Jeremiah

   Based on the code from the shop in Vingaard Keep.

*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include <language.h>
#include <cmdparse.h>
#include <macros.h>
inherit TOWERROOM;
inherit "/d/Genesis/lib/shop";

#define STORE_ROOM  WTOWER + "store"

object shopkeeper;
object *item_arr, *weapon_arr, *armour_arr, *misc_arr, to;

/* Prototypes */

string price_long(string str);

/*
 * Function name:       reset_room
 * Description:         Is called to reset the shopkeeper and room.
 * Returns:
 */
void
reset_tower_room()
{
    if (!shopkeeper)
    {
        shopkeeper = clone_object(WNPC + "shopkeeper.c");
        shopkeeper->move(TO);
    }
}


/*
 * Function name:   create_room
 * Description:     Initialize this room
 */

void
create_tower_room()
{
    reset_tower_room();

    set_short("The local shop");
    set_long("You are standing in the shop in the Tower of Wayreth. " +
             "Here you can buy and sell different kinds of merchandise " + 
             "for a fair price. The walls are lined with shelves and " +
             "boxes. Everything is clean and kept neatly ordered. " +
             "There is a small sign, with instructions on how to use " +
             "this shop, hanging on the wall.\n");
    
    config_default_trade();
    set_money_greed_buy(90);
    set_money_greed_sell(100);
    set_store_room(STORE_ROOM);

    add_cmd_item("sign", "read", "@@do_read");
    add_cmd_item(({"list","pricelist","prices"}), ({"read"}), 
                   "@@price_long");

    add_item("sign", "This is very nice looking sign. Written with " +
             "delicate golden letters on a dark grey background. " +
             "You are quite sure you understand the language in which " +
             "it is written, perhaps you should read it.\n");
    add_item(({"list","pricelist","prices"}), "It is a list showing " +
             "the current inventory of the shop. Your sensitive mind " +
             "detects a vague aura of magic coming from this list. " +
             "You are quite sure the list didn't look like this the " +
             "last time you were here looking at it. Perhaps you should " +
             "have a look at it again.\n");


    set_wall_type(2);
    add_exit(WTOWER + "lobby", "east", 0);
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();     /* You MUST do this in a room-init */
    init_shop();  /* Get the commands from the shop  */
}


int
do_read(string str)
{
   if(str == "sign")
   {
      write("                          -=Instructions=-\n");
      write("    buy <item> for <type> coins   (default: coins of " +
            "lowest value)\n");
      write("    buy <item> for <type> coins and get <type> coins back\n");
      write("    Beware, you will never buy more than one item at a time. " +
            "So if you really\n");
      write("    want those three pouches, you have to repeat yourself " +
            "three times.\n");
      write("    sell <item> for <type> coins  (default: coins of highest " +
            "value)\n");
      write("    sell <item>, sell second <item>, sell <item> 2 and sell " +
            "two <items> also\n");
      write("                works\n");
      write("    sell all  - will let you sell all items except for items " +
            "you wield or wear\n");
      write("                Beware, that if you have many items to sell, " +
            "check whether you\n");
      write("                have sold all or repeat the command.\n"); 
      write("    sell all! - will let you sell ALL items you have, well " +
            "at least the drop-\n");
      write("                pable ones, and no coins. (see warning at " +
            "'sell all')\n");
      write("    value     - will value an item you carry before you decide " +
            "to sell it.\n");
      write("    show      - appraise one of the items in stock before you " +
            "buy it.\n");
      write("    list      - will list the items in stock, 'list pouches' " +
            "and 'list torches'\n                will work too.\n");
      write("    IMPORTANT - I will NOT buy weapons or armours since " +
            "these will be of\n");
      write("                no use to me.\n");
      return 1;
   }
   return 0;
}
   

int
do_buy(string str)
{
   int buy_ok;

   buy_ok = ::do_buy(str);

/*
   if(buy_ok)
      tell_room(TO, "The list on the wall shimmers slightly and " +
                "seems to change.\n", TO);
*/
   return buy_ok;
}


/*                                                                       
* Function name: do_sell                                                 
* Description:   Try to let the player sell the_item                     
*                Observe there is no message written when sold item      
*                has a value higher than the shop gives out.             
* Returns:       1 on sucess                                             
* Arguments:     str - string holding name of item, hopefully            
*                    THANKS GO TO OLORIN                                 
*/                                                                       
int                                                                      
do_sell(string str)                                                      
{                                                                        
   object *item, *tmp_item;
   int value, check, ii, tmp;                                                 
   string str1, str2;                                                    
                                                                         
   if (!str || str =="")                                                 
   {                                                                  
      notify_fail("Sell what?\n");                                       
      return 0;                                                          
   }                                                                     
                                                                         
   /*  Did player specify how to get the money? */                             
   if (sscanf(str, "%s for %s", str1, str2) != 2)                           
   {                                                                        
      str1 = str;                                                              
      str2 = "";                                                               
   }                                                                           
                                                                               
   check = 1; /* Nothing worn or wielded will be sold. */                      
                                                                               
   if (str1 == "all!")                                                         
   {                                                                        
      str1 = "all";                                                            
      check = 0; /* Unless the player wants it. */
   }                                                                           
                                                                               
   item = FIND_STR_IN_OBJECT(str1, this_player());                             
   if (!sizeof(item))                                                          
      return shop_hook_sell_no_match(str1);                                    
                                                                               
   /* remove armours and weapons from the list of items to sell */
   /* We do not trade in armours or weapons in this shop.       */

   tmp_item = ({ });

   for(tmp = 0; tmp < sizeof(item); tmp ++)
   {
      if((weapon_filter(item[tmp])) || (armour_filter(item[tmp])))       
         write("Demitrius says: I will not buy your " + item[tmp]->short() +
               ".\n");
      else
         tmp_item = tmp_item + ({ item[tmp] });
   }

   item = sell_it(tmp_item, str2, check);            
   if (sizeof(item))                                                           
   {
      tell_room(TO, "The list on the wall shimmers slightly and " +
                "seems to change.\n", TO);
      return shop_hook_sold_items(item);                                    
   }

   if (str1 == "all") 
      return shop_hook_sold_nothing();                                     
                    
   if (!sizeof(item))
      return shop_hook_sold_nothing();

   return 0; /* Player tried to sell a non sellable object. */             
}


int
do_list(string str)
{
    write(price_long(str));
    say(QCTNAME(TP)+" looks at the pricelist.\n");
    return 1; 
}

string
text_short(int *mon_arr)
{
    string str = "";
    string *type = ({ "cc", "sc", "gc", "pc" });
    int i;

    if (sizeof(mon_arr) != 4)
	return "---";

    for (i=3; i>=0; i--)
    {
	if (mon_arr[i] > 0)
	{
	    str += sprintf("%2d %s ", mon_arr[i], type[i]);
	}
	else
	    str += "      ";
    }
    return str;
}

string
price_str(string str, int value)
{
    string *list = ({});
    string ret;
    int len, i;

    if (strlen(str)>37)
    {
	list = explode(break_string(str, 35), "\n");

	ret = list[0] + "\n";
	for (i=1; i<sizeof(list)-1; i++)
	    ret += "   " + list[i] + "\n";

	if (sizeof(list) > 1)
	    ret += "   " + list[sizeof(list)-1];

	len = strlen(list[sizeof(list)-1])+3;
    }
    else
    {
	ret = str;
	len = strlen(ret);
    }

    ret += "..............................................."[0..39-len];

    return ret + ":" + text_short(split_values(value)) + "\n";
}

/*
 * Function name:   price_long
 * Description:     Give a list of all objects in the STORE_ROOM.
 *                  The items on the list are categorized and numbered.
 * Returns:         A string with the above described list.
 */
string
price_long(string str)
{
    int i, value, previous;
    string the_long, tmp, fill_str;
    
    /* This is a VBFC function, so make sure our euid is set */
    seteuid(getuid());
    
    /* Force STORE_ROOM to be loaded */
    (STORE_ROOM)->short();
    item_arr = all_inventory(find_object(STORE_ROOM));
    if (!sizeof(item_arr))
      return "The drugstore is empty at the moment.\n";

    if (str)
      item_arr = FIND_STR_IN_ARR(str, item_arr);
        
    to = this_object();
    misc_arr = filter(item_arr, "misc_filter", to);
    
    fill_str = "                     ";
    previous = 1;
    
    the_long  = "\n-------------------------- Inventory ---------------------------\n";
    if (!sizeof(misc_arr))
      the_long += "   None\n";
    else
      {
	  for (i = 0; i < sizeof(misc_arr); i++)
	    {
		tmp = " " + C(LANG_ASHORT(misc_arr[i]));
		value = query_buy_price(misc_arr[i]);
		the_long += price_str(tmp, value);
	    }
      }
    
    the_long += "----------------------------------------------------------------\n";
    the_long += "\n";
    return the_long;
}

/* Function to identify things that are neither a weapon nor an armour */
int
misc_filter(object obj)
{
    return (!living(obj)) &&
	(member_array(obj, weapon_arr) < 0) &&
	(member_array(obj, armour_arr) < 0);
}
