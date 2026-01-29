/* the recruiter of the thieves, by Aridor 12/13/95*/

#include "../guild.h"
inherit M_FILE
inherit "/d/Genesis/lib/shop";
inherit "/lib/store_support";

#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <money.h>
#include <language.h>
#define MAXLIST 30

object *myownstuff = ({});

void
create_merchant()
{
    set_name("merchant");
    set_title("the Merchant");
    set_long("This is a travelling merchant who trades whatever he is " +
	     "carrying around. Use the commands 'list', 'buy', 'value', " +
	     "'show' and 'sell' just like in any normal shop.\n");
    set_race_name("human");
    default_config_mobile(50);
    set_all_attack_unarmed(40, 40);
    set_all_hitloc_unarmed(40);
    set_skill(SS_TRADING, 80);
    set_skill(SS_APPR_OBJ, 80);
    set_skill(SS_APPR_VAL, 80);

    set_knight_prestige(-1);
    set_whimpy_dir("north");
    set_whimpy(50);

    set_introduce(1);
    
    set_pick_up(10);
}

nomask void
create_krynn_monster()
{
    create_merchant();
    enable_reset(100);
    config_default_trade();
    set_max_values(10,5);
    set_store_room(file_name(TO));
    set_money_greed_buy(105);
    set_money_greed_sell(105);
}

void
reset_merchant()
{
    (all_inventory(TO) - myownstuff)->remove_object();
    myownstuff -= ({ 0 });
}

nomask void
reset_monster()
{
    reset_merchant();
    ::reset_monster();
}

void
init_living()
{
    init_shop();
    ::init_living();
}

int
do_list(string str)
{
    object *item_arr;
    int i, max, price, *arr;

    call_other(store_room, "load_me");

    item_arr = all_inventory(find_object(store_room));
    item_arr -= myownstuff;

    if (!sizeof(item_arr))
    {
	shop_hook_list_empty_store(str);
	return 0;
    }

    if (str == "weapons")
        item_arr = filter(item_arr, "weapon_filter", this_object());
    else if (str == "armours")
            item_arr = filter(item_arr, "armour_filter", this_object());
    else if (str)
	item_arr = FIND_STR_IN_ARR(str, item_arr);

    if (sizeof(item_arr) < 1)
	return shop_hook_list_no_match(str);
 
    max = MIN(MAXLIST, sizeof(item_arr));
    for (i = 0; i < max; i++)
    {
	price = query_buy_price(item_arr[i]);
	shop_hook_list_object(item_arr[i], price);
    }

    if (max < sizeof(item_arr))
    {
	write("Truncated...\n");
    }

    return 1;
}

int
do_show(string str)
{
    object *item_arr;
    int i, *arr;

    call_other(store_room, "load_me");

    item_arr = all_inventory(find_object(store_room));
    item_arr -= myownstuff;

    if (!sizeof(item_arr))
    {
	shop_hook_list_empty_store(str);
	return 0;
    }

    item_arr = FIND_STR_IN_ARR(str, item_arr);

    if (sizeof(item_arr) < 1)
    {
	return shop_hook_list_no_match(str);
    }

    shop_hook_appraise_object(item_arr[0]);
    item_arr[0]->appraise_object();

    return 1;
}

int
do_buy(string str)
{
    object *item, store;
    string str1, str2, str3;

    if (!str || str =="")
    {
	notify_fail("Buy what?\n");
	return 0;
    }
 
    call_other(store_room, "load_me"); /* Make sure storeroom is loaded */

    /*  Did the player specify payment and change? */
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s for %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    store = find_object(store_room);
    item = FIND_STR_IN_OBJECT(str1, store);
    item -= myownstuff;

    if (!sizeof(item))
	return shop_hook_buy_no_match(str1);

    item = buy_it(item, str2, str3);
    if (sizeof(item))
	return shop_hook_bought_items(item);

    return 0; /* Player tried to buy a non buyable object. */
}

int
do_value(string str)
{
    object *item, store;
    int *arr, price, i, j, num, no_inv;

    if (!str || str =="")
    {
	notify_fail("Value what?");
	return 0;
    }

    num = sizeof(query_money_types());
    item = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(item))
	no_inv = 1;

    for (i = 0; i < sizeof(item); i++)
    {
	if (!::shop_hook_allow_sell(item[i]) ||
		!item[i]->query_prop(OBJ_I_VALUE) ||
		item[i]->query_prop(OBJ_M_NO_SELL)) 
	{
	    shop_hook_value_not_interesting(item[i]);
	    continue;
	}

	price = query_sell_price(item[i]);
	arr = give(price, this_player(), "", 1);
	shop_hook_value_held(item[i], text(arr[num .. 2 * num - 1]));
	j++;
    }

    call_other(store_room, "load_me");
    store = find_object(store_room);
    item = FIND_STR_IN_OBJECT(str, store);
    item -= myownstuff;

    if (!sizeof(item) && no_inv)
	return shop_hook_value_no_match(str);

    for (i = 0; i < sizeof(item); i++)
    {
	price = query_buy_price(item[i]);
	arr = split_values(price); /* A price with few coins possible */
	shop_hook_value_store(item[i], text(arr));
	j++;
    }	

    shop_hook_value_asking(str);
    if (j > 0)
	return 1;

    return 0;
}

int
shop_hook_allow_sell(object obj)
{
    int val = obj->query_prop(OBJ_I_VALUE);
    
    if (MONEY_ADD(TO,-val))
      return 1;

    command("say I can't afford to buy " + LANG_THESHORT(obj) + ".");
    NF("");
    return 0;
}

