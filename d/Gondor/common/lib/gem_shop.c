/*
 *  Master Gem Shop for Jewellers
 *  (does not inherit room code -
 *   it does since it uses now /d/Gondor/common/lib/shop)
 *
 *  Coded by Olorin, 10-Nov-1994
 *
 *  using the Minas Morgul herb shop as example
 *
 *  shop must call init_shop() in init(), setup_gem_shop() in create_room()
 *
 *  Modification Log: 
 *  7 Feb. 2000, Stern : adapted for Genesis gem system, while still
 *                       accepting Gondor gems.
 */

inherit "/d/Gondor/common/lib/shop";
inherit "/lib/trade";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define STDGEMFILE 	(OBJ_DIR + "gems")
#define GEM_DIR         "/d/Genesis/gems/obj/"

#define MAXLIST		30
#define NUM 4
#define MONEY_TYPE ({ "cc", "sc", "gc", "pc" })


void
setup_gem_shop()
{
    // this line needed to created default trade configuration
    config_default_trade();

    set_money_greed_buy(60);
    set_money_greed_sell(120);

    set_money_give_max(10000);
    set_money_give_out(   ({  100,  1000, 1000,  25 }));
    set_money_give_reduce(({    0,     2,    4,  10 }));
}

int
shop_hook_allow_sell(object ob)  /*If not an herb, don't take it*/
{
    if ((function_exists("create_heap", ob) != STDGEMFILE) &&
      (!ob->query_gem()))
    {
	NF("The shopkeeper says: I'm sorry, I do not trade in anything but jewels.\n");
	return 0;
    }

    if (ob->query_value() > money_give_max)
    {
	if (ob->num_heap() > 1)
	{
	    NF("The shopkeeper says: I'm afraid I cannot afford to pay that much.\n"
	      + "The shopkeeper says: Perhaps you could try to sell the "+ob->short()+" singly.\n");
	    return 0;
	}
	write("The shopkeeper says: I'm afraid I cannot afford to pay the full value.\n");
    }
    return 1;
}

int
gem_filter(object ob)
{
    return ((function_exists("create_heap", ob) == STDGEMFILE) ||
      ob->query_gem());
}

/*
 * Function name: shop_hook_list_empty_store
 * Description:   If the storeroom is empty when the player wants a list
 *		  of its items
 * Arguments:	  str - If player specified string
 */
void
shop_hook_list_empty_store(string str)
{
    notify_fail("There are currently no jewels for sale.\n");
}

/*
 * Function name: shop_hook_list_other
 * Description:   List an object other than a herb
 * Arguments:	  ob - The object
 */
void
shop_hook_list_other(object ob, int price)
{
    string str, mess;

    str = sprintf("  %-20s - ", capitalize(ob->short()));
    if (mess = text(split_values(price)))
	write(str + mess + ".\n");
    else
	write(str + "That item wouldn't cost you much.\n");
}

/*    
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns: 	  The price
 */
int
query_buy_price(object ob)
{
    int     seed;

    sscanf(OB_NUM(ob), "%d", seed);

    return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
      15 - this_player()->query_skill(SS_TRADING) / 4 +
      random(15, seed)) / 100;
}

/*
 * Function name:   do_list
 * Description:     Provide a list of objects in the store room
 * Returns:         0 if not recognised
 *                  1 otherwise
 * Arguments: 	    str - the name of the objects to search for
 */
int
do_list(string str)
{
    object *item_arr;
    int i, price, *arr, num;

    call_other(store_room, "load_me");

    item_arr = all_inventory(find_object(store_room));

    if (!sizeof(item_arr))
    {
	shop_hook_list_empty_store(str);
	return 0;
    }

    if (str)
	item_arr = FIND_STR_IN_ARR(str, item_arr);

    if (sizeof(item_arr) < 1)
	return shop_hook_list_no_match(str);


    for (i = 0; i < sizeof(item_arr); i++)
	if (i < MAXLIST)
	{
	    price = query_buy_price(item_arr[i]);
	    if ((num = item_arr[i]->num_heap()) > 1)
		price /= num;
	    shop_hook_list_object(item_arr[i], price);
	}
	else
	{
	    write("Truncated: " + i + ".\n");
	    break;
	}

    return 1;
}

/* The idea for this routine is got from Padermud. --Randor
 */
mixed
neat_text(int *arr)
{
    int     i;
    string  temp;

    if (sizeof(arr) < NUM) /* invalid array */
	return;

    temp = "";
    for (i = NUM - 1; i >= 0; i--)
    {
	if (arr[i] > 0)
	    temp += sprintf("%2d %2s ", arr[i], MONEY_TYPE[i]);
	else
	    temp += "      ";
    }
    return temp;
}

void
shop_hook_list_object(object ob, int price)
{
    string  str,
    mess;
    int     num;

    mess = neat_text(split_values(price));

    if ((num = ob->num_heap()) == 0)
	num = 1;


    if (!stringp(mess))
	mess = "That item wouldn't cost you much.\n";
    write(BSN(sprintf("%-15s (in stock: %4d ) - %20s", 
          CAP(ob->query_pname()), num, mess)));
    /*
	    write(BSN(sprintf("%4d %-35s %20s", num,
		CAP(ob->query_gem_type()), mess)));
    */
}

/*
 * Function name: buy_it
 * Description:   Try to let the player buy the item array
 * Arguments:     ob - the object array
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       1 on sucess
 */
object *
buy_it(object *ob, string str2, string str3) 
{
    int price, i, j, k, *value_arr, *arr, error, num, err;
    object *bought;
    mixed tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);
    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
	if (!shop_hook_allow_buy(ob[i]))
	    continue;

	if (tmp = ob[i]->query_prop(OBJ_M_NO_BUY))
	{
	    shop_hook_buy_no_buy(ob[i], tmp);
	    continue;
	}

	price = query_buy_price(ob[i]);

	/* be sure they can pay before we try to move ob to player,
	 * because if ob is a heap and the move succeeds and the player
	 * is holding another of that ob, they will merge.
	 * too late then to discover that the player can't pay.
	 * set 'test' (4th) arg so this call doesn't actually move coins
	 */
	if (sizeof(arr = pay(price, this_player(), str2, 1, 0, str3)) == 1)
	{
	    shop_hook_buy_cant_pay(ob[i], arr);
	    continue;
	}


	/* If you don't feel greedy you can shorten the calculation above. */

	if (err = ob[i]->move(this_player()))
	{
	    shop_hook_buy_cant_carry(ob[i], err);
	    continue;
	}

	if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
	{
	    ob[i]->move(store_room, 1);
	    shop_hook_buy_cant_pay(ob[i], arr);
	    continue;  /* pay() can handle notify_fail() call */
	}

	/* Detect if there was a move error. */
	if (error = arr[sizeof(arr) - 1])
	{
	    if (error < -1)
	    {
		/* Couldn't take the money from player, the coins were stuck */
		shop_hook_buy_magic_money(ob[i]);
		ob[i]->move(store_room, 1);
		continue;
	    }
	    /* We don't want the money so no move error to us, if there was one
	       it was because the player couldn't hold all coins, and if so the
	       drop text is already written, but the deal is still on :) */
	}

	for (k = 0; k < 2 * num; k++)
	    value_arr[k] += arr[k];

	bought[j] = ob[i];
	j++;
	if (j >= 1)
	    break;
	/* Well, we don't want to let a player accidentily buy too much :) */
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
	shop_hook_buy_pay_money(
	  text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));

    return bought;
}
