/*
 *  The shop of the Rangers of Gondor.
 *  - Modified to use Olorin's standard-Gondor-shop, July 1994.
 *  - Modified by Randor 1992
 *  - From the Hobbiton Shop, 1991, by Elessar.
 *
 *  27-Feb-98, Gnadnar:	allow players to "show" std equipment,
 *	remove repeated calls to sizeof in loops.
 *  Adapted by Morrigan to use for the mercenary guild shop
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/shop.c";

#include "../merc.h"
#include "room.h"

         /* Where are the items stored? */
#define STORE_ROOM (MROOM + "store")
#define MERC_EQUIP ({	MOBJ + "backpack", \
			MOBJ + "sack", \
			MOBJ + "oil_lamp", \
			MOBJ + "oilflask", \
                        MOBJ + "boots", \
			MOBJ + "boot_sheath", \
			MOBJ + "whetstone", })

public void create_shop();
public string exa_poster();
public void set_standard_equip(mixed x);
public object *clone_and_buy_it(string str1, string str2, string str3);
public object clone_it(string str);
public int do_buy(string args);
public int do_list(string args);
public int do_show(string str);

static string *standard_equip;
string *sold_list = ({});

public int exit_tent()
{
	write(TENT_EXIT);
}

public void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("A small tent");
    set_long("This tent is obviously a shop of sorts. You notice a "+
	"poster hanging on the wall by the counter.\n");
    set_shop_name("Mercenary Camp Shop");
    set_keeper_file(MNPC + "soren");
    add_item("counter", "The counter is where the transactions take place.\n");
    add_item("poster","It has readable words on it.\n");
    add_exit(MROOM + "center", "southwest", "@@exit_tent", 0,0);
    set_standard_equip(MERC_EQUIP);
}

public string
exa_poster()
{
  return "\nWelcome to the Shop of the Mercenary Camp!\n" +
         "You can try these instructions: \n" +
         "    buy sword for gold and get copper back\n" +
         "    buy sword for gold coins\n" +
         "    sell sword for copper coins\n" +
         "    sell all  - will let you sell all items except for\n" +
         "                items you wield or wear.\n" +
         "    sell all! - will let you sell ALL items you have, well\n" +
         "                at least the droppable, and no coins.\n" +
         "    sell sword, sell second sword, sell sword 2, sell two swords\n" +
         "                also works. You might want to change the verb to\n" +
         "                'value' or 'buy' too. Beware, you will never buy\n"+
         "                more than one item at a time. So if you really\n" +
         "                want those three expensive swords, you have to \n" +
         "                repeat yourself three times.\n" +
	 "    If you want a list of the special equipment available, do:\n"+
         "     'list equipment'.\n"+
         "    If you want a list of all swords available in the store, the\n" +
         "    correct syntax is: list swords\n" +
         "                'list weapons', 'list armours' also works.\n\n"+
	 "Hastily written at the bottom of the poster are the words: Please\n"+
	 "do not kill the shopkeeper, he is not being rude, he is mute.\n\n";
}

public void
set_standard_equip(mixed x)
{
    if (stringp(x))
        standard_equip = ({ x });
    else if (pointerp(x))
        standard_equip = x;
    else
        standard_equip = MERC_EQUIP;
}

object
clone_it(string str)
{
    int n, s;
    object ob;
    string *s_arr,
        *adjs;

    seteuid(getuid());

    s_arr = explode(str, " ");
    if ((s = sizeof(s_arr)) > 1)
        str = s_arr[s - 1];
    s_arr -= ({ str });
    --s;
    n = -1;
    while (++n < sizeof(standard_equip) && !objectp(ob))
    {
        if (standard_equip[n]->id(str))
        {
            adjs = standard_equip[n]->query_adjs();
            if (!s || (s == sizeof(adjs & s_arr)))
                ob = clone_object(standard_equip[n]);
        }
    }

    return ob;
}

object *
clone_and_buy_it(string str1, string str2, string str3)
{
    int price, i, j, k, n,
        num = sizeof(query_money_types()),
        *value_arr = allocate(2 * num),
        *arr, error, err;
    object ob;

    if (!strlen(str1))
	return 0;

    ob = clone_it(str1);
    if (!objectp(ob))
    {
	return 0;
    }

    price = query_buy_price(ob);
  
    if (err = ob->move(this_player()))
    {
        shop_hook_buy_cant_carry(ob, err);
        ob->remove_object();
        return 0;
    }
  
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
    {
        shop_hook_buy_cant_pay(ob, arr);
        ob->remove_object();
        return 0;
    }
  
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
            /* Couldn't take the money from player, the coins were stuck */
            shop_hook_buy_magic_money(ob);
            ob->remove_object();
        }
        /* We don't want the money so no move error to us, if there was one
           it was because the player couldn't hold all coins, and if so the
           drop text is already written, but the deal is still on :) */
    }
  
    for (k = 0; k < 2 * num; k++)
        value_arr[k] += arr[k];
  
    if (objectp(ob))
        shop_hook_buy_pay_money(
            text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));
  
    return ({ ob });
}

public int
do_buy(string args)
{
    int     res;
    object *item;
    string  str,
        str2,
        str3;
  
    if (!args || args == "")
    {
        NF("The shopkeeper says: Buy what?\n");
        return 0;
    }

    if (sscanf(args,"%s for %s and get %s", str, str2, str3) != 3)
    {
        str3 = "";
	if (sscanf(args,"%s for %s", str, str2) != 2)
        {
	    str2 = "";
	    str = args;
        }
    }

    if (res = ::do_buy(args))
        return res;
    else
    {
	item = clone_and_buy_it(str,str2,str3);
	if (sizeof(item))
            return shop_hook_bought_items(item);
        else
            return 0;
    }
    return 0;
}

public int
do_list(string args)
{
    string list_txt;
    int n, s;

    if (args != "equipment" && args)
        return ::do_list(args);
    else if (!args || args == "")
    {
        ::do_list(args);
        write(" --- Standard equipment available by "+
 	  "'list equipment'.\n");
        return 1;
    }

    write(" Standard equipment in stock: "+
          "----------------------\n");
    s = sizeof(standard_equip);
    while (n < s)
    {
        call_other(standard_equip[n], "load_me");
        shop_hook_list_object(find_object(standard_equip[n]),
        query_buy_price(find_object(standard_equip[n])));
        n++;
    }

    write(" ----------------------------------------------"+
      "------------\n");
    return 1;
}

public mixed
shop_hook_filter_sell(object x)
{
    return 0;
}

/*
 * Function name: do_show
 * Description  : Allow the player to appraise one of the objects in stock.
 * Returns      : int - 1/0 - true if success.
 * Arguments    : string str - the name of the objects to search for.
 */
public int
do_show(string str)
{
    object ob;

    if (!str || str == "")
    {
        NF("The shopkeeper says: Show what?\n");
        return 0;
    }

    if (::do_show(str))
	return 1;

    if (!objectp(ob = clone_it(str)))
	return 0;

    shop_hook_appraise_object(ob);
    ob->appraise_object();
    ob->remove_object();
    return 1;
}

