/* 
 * Palanthas fishmonger. Arman 2021
 *
 */
#include "../local.h"

inherit SHIP_ROOMBASE;
inherit "/lib/shop";
inherit TDIR + "shop_list";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define STORE_ROOM      SHIP + "fishmonger_store"

#define ASSIGN_AND_VALIDATE_STORE_OBJECT(s_o) \
    s_o = get_store_object(); \
    if (!(s_o)) \
    { \
        write("Error: no store object - please make a bug report.\n"); \
        return 1; \
    }

string
query_to_jail()
{
  return "south";
}

void
reset_palan_room()
{
    return;
}

void
create_palan_room()
{
    config_default_trade();

    SHORT("Fish markets of Palanthas");
    LONG("A noisy fish market, where the locals come to get the " +
        "freshest fish from the nearby seas, and fisherman come " +
        "to sell their wares. There is a sign hanging from the " +
        "centre of the roof here with purchasing and selling " +
        "instructions painted in big bold letters.\n");

    // Set greed when person pays for a price, in %.
    // 100 means the price in the pay() call will not
    // be changed. >100 will make the player pay more.
    set_money_greed_buy(120);

    // Set greed when person sells something, in %
    // 100 means the price in the give() call will not
    // be changed. >100 will make the player get less.
    set_money_greed_sell(50);
    
    set_store_room(STORE_ROOM);

    ITEM("sign", "A sign hangs from the roof here. You may " +
        "<read> it.\n");
    ITEM(({"market","fish market"}),
        "A busy and noisy fish market, where Palanthians " +
        "come to get the freshest fish, and fisherman get " +
        "the best prices for their catch.\n");
    ITEM("fish","The fish market is full of fish. You can " +
        "<list> what is currently available for sale.\n");

    CMD("sign", "read", "@@read_sign");

    EXIT(SHIP + "s10","south", 0, 0);
    add_exit(STORE_ROOM, "north", "@@wiz_check", 0, 1);

    reset_palan_room();
}

object *
sell_it(object *ob, string str, int check)
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
    if (!shop_hook_allow_sell(ob[i]))
        continue;

    if (!ob[i]->id("global_fish_obj"))
    {
        write("You can only sell fresh fish here!\n");
        shop_hook_sell_no_value(ob[i]);
        continue;
    }

    if (ob[i]->query_prop(OBJ_I_VALUE) == 0)
    {
        shop_hook_sell_no_value(ob[i]);
        continue;
    }

    /* Save price if ob destructed in move */
    price = query_sell_price(ob[i]);

    if (price <= 0)
    {
        shop_hook_sell_no_value(ob[i]);
        continue;
    }

    if (err = ob[i]->move(store_room))
    {
        shop_hook_sell_object_stuck(ob[i], err);
        continue;
    }

    if (price > 0)
    {
        tmp_arr = calc_change(price, null, str);
        for (k = 0; k < sizeof(value_arr); k++)
        value_arr[k] += tmp_arr[k];

        sold[j] = ob[i];
        j++;
        if (j >= 20)
        break;
        /*
        * Only let people sell 20 objects at once and hopefully we wont get
        * those too long evaluation problems.
        */
    }
    }

    sold = sold - ({ 0 });

    if (sizeof(sold) > 0)
    {
    change_money(null_arr + value_arr, this_player());
    shop_hook_sell_get_money(text(value_arr));
    }

    return sold;
}

int
do_sell(string str)
{
    return ::do_sell(str);
}

/*
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */
int
do_value(string str)
{
    object *items;
    object store_object;
    int *arr, price, j, num, no_inv;

    if (!strlen(str))
    {
        notify_fail("Value what?\n");
	return 0;
    }

    num = sizeof(query_money_types());
    items = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(items))
    {
	no_inv = 1;
    }

    foreach(object item: items)
    {
	if (!item->id("global_fish_obj")) 
	{
	    shop_hook_value_not_interesting(item);
	    continue;
	}

	price = query_sell_price(item);
        arr = give(price, this_player(), "", 1);
	shop_hook_value_held(item, text(arr[num .. 2 * num - 1]));
	j++;
    }

    ASSIGN_AND_VALIDATE_STORE_OBJECT(store_object);
    items = find_str_in_object(str, store_object);

    if (!sizeof(items) && no_inv)
    {
	return shop_hook_value_no_match(str);
    }

    foreach(object item: items)
    {
	price = query_buy_price(item);
	arr = split_values(price); /* A price with few coins possible */
	shop_hook_value_store(item, text(arr));
	j++;
    }	

    shop_hook_value_asking(str);

    if (j)
    {
	return 1; 
    }

    return 0;
}

void
init()
{
        ::init();
        init_shop();
}


void
init_shop()
{    
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_show", "show");
        add_action("do_sell", "sell");
        add_action("do_value", "value");

}

public int
read_sign()
{
    say(QCTNAME(TP) + " reads the sign hanging from the roof.\n");
    write("The sign reads...\n" +
        "        PALANTHAS FISH MARKETS!\n\n\n" +
        "    <list> the fish catch that has been brought in!\n\n" +
        "    Want a closer look? We can <show> you!\n\n" +
        "    <buy> any fish that catches your fancy!\n\n" +
        "    <value> any fresh catch you have landed!\n\n" +
        "    <sell> any fresh catch if you like the price!\n\n");

    return 1;
}

int
wiz_check()
{
    if (this_player()->query_wiz_level())
          return 0;
    write("There is no obvious exit north.\n");

    return 1;
}
