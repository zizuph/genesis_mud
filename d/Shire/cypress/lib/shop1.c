/*
 *  The shop of the Rangers of Gondor.
 *  - Modified to use Olorin's standard-Gondor-shop, July 1994.
 *  - Modified by Randor 1992
 *  - From the Hobbiton Shop, 1991, by Elessar.
 *
 *  27-Feb-98, Gnadnar:	allow players to "show" std equipment,
 *	remove repeated calls to sizeof in loops.

 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/shop.c";
inherit "/d/Emerald/lib/shop_list";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/lode/defs.h"
#include "/d/Shire/cypress/lib/shop_items.h"

         /* Where are the items stored? */
#define STORE_ROOM "/w/finwe/workroom"


public void create_shop();
public string exa_poster();
public void set_standard_equip(mixed x);
public int discriminate();
public object *clone_and_buy_it(string str1, string str2, string str3);
public object clone_it(string str);
public int do_buy(string args);
public int do_value(string args);
public int do_list(string args);
public mixed shop_hook_filter_sell(object x);
public void enter_inv(object ob, object from);
public int do_show(string str);

static string *standard_equip;
string *sold_list = ({});

public void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("the Rangers Equipment Store");
    set_long(
      "You are in the Rangers Equipment Store. "+
      "There are lots of strange items lying around, probably brought "+
      "here from distant lands. There is a poster on the wall, and " +
      "the exit from the store leads back south.\n");
    set_shop_name("The Rangers Equipment Store");
    set_keeper_file("/d/Shire/esgaroth/npcs/shopkeeper");
    set_favoured_race(({"human","elf"}));
//    set_money_greed_sell("@@discriminate");
//    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");
    add_item("notebook", "@@look_notebook");
    add_item("poster","It has readable words on it.\n");
    add_item(({"door"}), 
        "The door is probably leading into the storeroom of the "+
        "shop. The door is standing open, but the shop keeper " +
        "probably would not be amused if you tried to go there. ");
    set_standard_equip(SHOP_EQUIP);

}

public string
look_notebook()
{
    if(!check_keeper())
    {
        return "You find no notebook.\n";
    }

    else
    {
        write("The shopkeeper pulls his notebook away from " +
            "your prying eyes, mumbling something about curiosity " +
            "and a dead cat.\n");
        say("The shopkeeper pulls his notebook away from " +
            QTPNAME(TP) + " prying eyes, mumbling something about " +
            "curiosity and a dead cat.\n");
        return "";
    }
}

public string
exa_poster()
{
  return "\nWelcome to the Rangers Equipment Store!\n" +
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
         "     'list supplies'.\n"+
         "    If you want a list of all swords available in the store, the\n" +
         "    correct syntax is: list swords\n" +
         "                'list weapons', 'list armours' also works.\n\n";
}

public void
set_standard_equip(mixed x)
{
    if (stringp(x))
        standard_equip = ({ x });
    else if (pointerp(x))
        standard_equip = x;
    else
        standard_equip = SHOP_EQUIP;
}

public int
discriminate()
{
    object tp = TP;
    string race = tp->query_race();
    int bargain = tp->query_skill(SS_TRADING);

    if (bargain > 30) 
        bargain = 30;
    bargain = 115 - bargain;
// yes, all elves get a break here
    if (member_array(race, favoured_race) > -1)
        bargain = (bargain * 98) / 100;

    return bargain;
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
  
    if (!check_keeper())
        return 0;
    else if (!args || args == "")
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
do_value(string args)
{
    if (check_keeper()) 
    {
        write("The shopkeeper is not here.\n");
    }
    return 0;
}

public int
do_list(string args)
{
    string list_txt;
    int n, s;
    if (!check_keeper()) 
    {
        return 0;
    }
    else
    {
        if (args != "supplies" && args)
            return ::do_list(args);
        else 
        {
            if (!args || args == "")
            {
                ::do_list(args);
                write(" *** Supplies available by 'list supplies ***'.\n");
                return 1;
            }
        
            write(" Elven supplies in stock: ----------------------\n");
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
    }
}

public mixed
shop_hook_filter_sell(object x)
{
    return 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from) || !objectp(ob) || !interactive(ob))
	return;

    if (!check_keeper())
	return;

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

    if (!check_keeper())

        NF("The shopkeeper says: Show what?\n");
        return 0;
//    }

    if (::do_show(str))
	return 1;

    if (!objectp(ob = clone_it(str)))
	return 0;

    shop_hook_appraise_object(ob);
    ob->appraise_object();
    ob->remove_object();
    return 1;
}
public void
init()
{
    ::init();
}
