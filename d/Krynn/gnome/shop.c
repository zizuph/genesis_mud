/* 
    Here I go borrowing code again.  Thanks, Nick. :)
						--Grrrr
   An example shop coded by Nick, some Ideas and part of code taken from 
   Tricky's shop in hobbitown.

*/

inherit "/d/Krynn/std/room";
inherit "/d/Emerald/lib/shop";

#include <macros.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"


#define STORE_ROOM TDIR + "store"
#define MAXLIST 30
#define BBS(xxx) break_string(xxx,75)
#define NUM 4

public void reset_room();
object *item_arr, *weapon_arr, *armour_arr, *misc_arr, to;

/* Prototypes */
string price_long(string str);

public void
reset_room()
{
    return;
}

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
    seteuid(getuid(TO));
    config_default_trade();

    set_store_room(STORE_ROOM);
    (STORE_ROOM)->load_me();

    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_max(1100);
    set_money_give_out(({10000, 700, 40, 1}));
    set_money_give_reduce(({0, 4, 3, 9}));

    set_short("ThePlaceWherePeopleComeToBuyAndSellThingsAtMutuallyAgreedUponPrices");
    set_long(BS("Welcome to the Commerce Guild headquarters for this " +
	"settlement. The gnomes affectionately refer to this place as: " +
    "ThePlaceWherePeopleComeToBuyAndSellThingsAtMutuallyAgreedUponPrices. " +
	"The actual name is longer, but you get the idea.  A sign " +
	"hangs behind the counter.", 70));

    add_cmd_item("sign", "read", "@@do_read");
    add_item("sign", "@@read");

    add_exit("/d/Krynn/guilds/gnomes/rooms/joinroom.c", "west", 0);
    add_exit(STORE_ROOM, "east", "@@wiz_check");

    INSIDE;
    LIGHT;

    reset_room();
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop();
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
    write("A long mechanical arm extends out of the store room and pushes you back.\n");
    say(QCTNAME(this_player()) + " tries to go east but is pushed back.\n");
    return 1;
}

/*
 * Function name:   do_read
 * Description:     If a player wants to know what instuctions can be
 *                  used
 * Arguments:       str - string, hopefully "sign"
 * Returns:         1/0
 */
string
read()
{
    string str;
    str ="" +
    "Welcome to Theplacewherepeoplecome...  Oh, never mind.\n" +
    "\nYou can try these instructions: \n" +
    "    buy sword for gold and get copper back\n" +
    "    buy sword for gold coins\n" +
    "    sell sword for copper coins\n" +
    "    'sell all'  will let you sell all items except for\n" +
    "                items you wield or wear.\n" +
    "    'sell all!' will let you sell ALL items you have which\n" +
    "                are droppable, and not coins.\n" +
    "    'sell sword', 'sell second sword', 'sell sword 2', 'sell two swords'\n" +
    "                are all permitted.\n" +
    "    The same variations work for 'buy' and 'value', though\n" +
    "                you can never buy more than one item at a time.\n" +
    "    'list', 'list armours', 'list weapons', 'list <name>' will all list\n" +
    "                the corresponding items for you.\n" +
    "                Use the singular for <name>, as in 'list sword'.\n";
    return str;
}

do_read(){
    string str;
    str = read();
    write(str);
    return 1;
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
      return "The store is empty at the moment.\n";
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

public void
shop_hook_buy_pay_money(string str, string change)
{
    write("You give " + str + " to the shopkeeper.\n");
    if (change)
        write("The shopkeeper gives you " + change + " back.\n");
}

