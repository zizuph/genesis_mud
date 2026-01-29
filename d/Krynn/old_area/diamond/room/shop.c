/*
   Diamond. Supply Shop

   shop.c
   ------

   Coded ........: May 1997
   By ...........: Kentari

   Latest update : October 1997
   By ...........: Kentari

   Based on the code from the shop in Vingaard Keep.

*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <language.h>
#include <cmdparse.h>
#include <macros.h>
inherit IN_BASE;
inherit "/d/Genesis/lib/shop";

#define STORE_ROOM  DIROOM + "store1"

object shopkeeper;
object *item_arr, *weapon_arr, *armour_arr, *misc_arr, to;

/* Prototypes */

string price_long(string str);


void
reset_dim_room()
{
    if (!shopkeeper)
    {
        shopkeeper = clone_object(DINPC + "shopkeeper.c");
        shopkeeper->move(TO);
    }
}


void
create_dim_room()
{
    set_short("The supply shop");
    set_long("You are in the supply shop of Diamond City. Here you can " +
	     "buy drinking and adventuring supplies (In case " +
	     "you'd like to continue the merriment elsewhere). " +
             "There is a small sign, with instructions on how to use " +
             "this shop, hanging on the wall.\n");
    
    config_default_trade();
    set_money_greed_buy(80);
    set_money_greed_sell(75);
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

    add_exit(DIROOM + "se2", "northwest", 0);
    add_exit(STORE_ROOM, "down", "@@wiz_check");
    query_store_room()->load_me();

    reset_dim_room();
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
      write("    want those three bottles, you have to repeat yourself " +
            "three times.\n");
      write("    show      - appraise one of the items in stock before you " +
            "buy it.\n");
      write("    list      - will list the items in stock, 'list pouches' " +
            "and 'list torches'\n                will work too.\n");
      return 1;
   }
   return 0;
}
   

int
do_buy(string str)
{
   int buy_ok;

   buy_ok = ::do_buy(str);

   if(buy_ok)
      tell_room(TO, "The list on the wall shimmers slightly and " +
                "seems to change.\n", TO);

   return buy_ok;
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

    if (strlen(str)>28)
    {
	list = explode(break_string(str, 26), "\n");

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

    ret += "..............................................."[0..30-len];

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
      return "The supply shop is empty at the moment.\n";

    if (str)
      item_arr = FIND_STR_IN_ARR(str, item_arr);
        
    to = this_object();
    misc_arr = filter(item_arr, "misc_filter", to);
    
    fill_str = "                     ";
    previous = 1;
    
    the_long  = "\n---------------------- Inventory -----------------------\n";
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
    
    the_long += "--------------------------------------------------------\n";
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

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
int
wiz_check()
{
    if (this_player()->query_wiz_level())
	return 0;
    write("You are not allowed in the store room!\n");
    say(QCTNAME(this_player()) + " tries to enter the store room but fails.\n");
    return 1;
}

