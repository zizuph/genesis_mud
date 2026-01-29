/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include "/sys/money.h"
#include <macros.h>
#include <cmdparse.h>

inherit INNER_IN;
// inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";
inherit "/d/Emerald/lib/shop";

#define STORE_ROOM    NINNER + "shop_store"
#define MAXLIST 30
#define BBS(xxx) break_string(xxx,75)

object *item_arr, *weapon_arr, *armour_arr, *misc_arr, to;

/* Prototypes */
string price_long(string str);

void
create_neraka_room()
{
    set_short("inside a fancy shop");
    set_shop_name("Inner Temple Exotic Shop");
    set_long("You have entered a large shop housed in a fancy building. " +
        "There are shelves along the walls and a bench stands against one " +
        "wall, bearing a sign. An oil lamp is mounted on the wall, " +
        "illuminating the room. There is a doorway leading north out " +
        "of the shop.\n");

    add_item_inside();
    add_item(({"shelf","shelves"}),"Shelves line the walls, filled with " +
        "various pieces of armour.\n");
    add_item("bench","The bench stands against one wall. A large sign rests " +
        "on top of the bench, against the wall.\n");
    add_item(({"lamp","oil lamp"}),"The lamp sheds some light in the room, " +
        "enough to read by.\n");
    add_item("doorway","The doorway leads north, out of the shop.\n");

    add_item("sign", "It is a sign of instructions.\n");
    add_cmd_item("sign", "read", exa_poster());

    add_exit(NINNER + "r41","north","@@msg");

    config_default_trade();
    set_money_greed_buy(105);
    set_money_greed_sell(110);

    set_store_room(STORE_ROOM);
}

int
msg()
{
    write("You leave the shop and exit onto the street.\n");
    return 0;
}

void
init()
{
	::init();
    init_shop();
}


int
do_buy(string str)
{
    if (check_cheater(TP))
        return 1;
    return ::do_buy(str);
}

int
do_sell(string str)
{
    if (check_cheater(TP))
        return 1;
    return ::do_sell(str);
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
