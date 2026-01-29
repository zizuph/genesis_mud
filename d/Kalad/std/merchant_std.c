inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#pragma stricty_types
#pragma save_binary
#define NUM sizeof(MONEY_TYPES)

/*                                                              *
 * Merchant base. Used for creating a merchant who sells items  *
 * to buy.                                                      *
 * By Sarr, 14.Jul.97                                           *
 *                                                              *
 * Functions to define:                                         *
 * void                                                         *
 * add_merchant_item(string name, int price, string file_name, string desc) *
 * string hook_merchant_list_wares()                            *
 * string hook_merchant_no_item()                               *
 * void set_list_command(string command)                        *
 *                                                              *

/* The variable that holds the item list */
/* Should be : ({"item name",price,"file name","description"}) */
/* Example: ({"silver necklace",230,"/d/Kalad/sarr/necklace","A beautiful
   necklace to give a loved one"})                              */

mixed *merchant_item_list;

void
add_merchant_item(string name, int price, string fname, string desc)
{
    if(!sizeof(merchant_item_list))
	merchant_item_list = ({});
    merchant_item_list += ({ ({name,price,fname,desc}) });
}

/* Set the string to ask of the merchant to get a list of its   */
/* items, ie set_list_command("wares") will get the merchant to */
/* list its items when asked 'wares'.                           */

void
set_list_command(string str)
{
    add_ask(str,VBFC_ME("wares_return"));
}

/* The string to start at the header of the list of items */

string
hook_merchant_list_wares()
{
    return "I have the following items to sell:\n";
}

/* The string to return if we don't have that item. The arg is a */
/* string of what item we did not find */

string
hook_merchant_no_item(string item)
{
    return "I don't have any '"+item+"' in my stock.\n";
}

string
wares_return()
{
    string list;
    int i;
    list = hook_merchant_list_wares();
    for(i=0;i<sizeof(merchant_item_list);i++)
    {
	list += merchant_item_list[i][0]+" - "+
	merchant_item_list[i][3]+" --- "+merchant_item_list[i][1]+
	" coppers\n";
    }
    return list+"\nDo buy <item> to purchase.\n";
}

void
create_merchant()
{
}

void
create_monster()
{
    set_name("merchant");
    set_long("This is a merchant.\n");

    set_stats( ({40,40,43,50,50,30}) );
    default_config_trade();
    create_merchant();
}


void
init_living()
{
    ::init_living();
    AA(do_buy,buy);
}

int
do_buy(string str)
{
    object item;
    string str2,str3;
    int *arr, num, i, iprice;

    seteuid(getuid());


    for(i=0;i<sizeof(merchant_item_list);i++)
    {
	if(str == merchant_item_list[i][0])
	{
	    iprice = merchant_item_list[i][1];
	    item = clone_object(merchant_item_list[i][2]);
	}
    }
    NF(hook_merchant_no_item(str));
    if(!objectp(item))
	return 0;

    if (sizeof(arr = pay(iprice, this_player(), str2, 0, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
	write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("You get a "+item->short()+".\n");
    say(QCTNAME(TP)+" gets a "+item->short()+".\n");
    if(item->move(TP))
    {
	write("Its too heavy, and you drop it.\n");
	item->move(E(TP));
    }
    return 1;
}
