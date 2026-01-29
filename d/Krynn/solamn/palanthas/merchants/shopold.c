/* 
 * Mortis 03.2006
 *
 * Palanthas shop.
 *
 */

#include "../local.h"

inherit MERCH_ROOMBASE;
inherit "/lib/shop";
inherit TDIR + "shop_list";

#include <macros.h>
#define STORE_ROOM      MERCH + "store"
#define VK_NOBUY		 "_vkeep_shop_no_buy"

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
	config_default_trade();

	SHORT("Shop of Palanthas");
	LONG("A simple store of polished translucent marble.  There is a "
	+ "counter along the west wall curving around to the north and a "
	+ "marble sign hanging behind the counter.\n");

	set_money_greed_buy(80);
	set_money_greed_sell(75);
	
	set_store_room(STORE_ROOM);

	ITEM("sign", "A marble sign hangs behind the counter along the west "
	+ "wall.  You may <read> or <mread> it.\n");
	ITEM("counter", "A marble display counter curves along the west wall "
	+ "to the north.  You may see what is for sale with <list>.\n");
	ITEM("marble", "The shop is built of polished, translucent white "
	+ "marble common in Palanthas construction.\n");

	CMD("sign", "read", "@@read_sign");
	CMD("sign", "mread", "@@mread_sign");

	EXIT(MERCH + "m04","east", 0, 0);
	EXIT(STORE_ROOM, "north", "@@wiz_check", 0);

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

	if (ob[i]->query_prop(VK_NOBUY))
	{
		write("We do not purchase illegally obtained goods here!\n");
	    shop_hook_sell_no_value(ob[i]);
	    continue;
	}

	if (ob[i]->query_prop(OBJ_I_VALUE) == 0)
	{
	    shop_hook_sell_no_value(ob[i]);
	    continue;
	}

	if (check && (ob[i]->query_worn() ||
	    ob[i]->query_wielded()))
	{
	    shop_hook_sell_worn_or_wielded(ob[i]);
	    continue;
	}

	if (tmp = ob[i]->query_prop(OBJ_M_NO_SELL))
	{
	    shop_hook_sell_no_sell(ob[i], tmp);
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
	say(QCTNAME(TP) + " reads the marble sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/shop_sign.txt", 1, 50);

	return 1;
}

public int
mread_sign()
{
	string file = MERCH + "obj/shop_sign.txt";

	say(QCTNAME(TP) + " studies the marble sign on the west wall.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

int
wiz_check()
{
    if (this_player()->query_wiz_level())
      	return 0;
    write("The north passage is not for the likes of you.  You decide "
	+ "against treading upon the affairs of the store room.\n");
    say(QCTNAME(TP) + " contemplates violating the sanctity of the store "
	+ "room, but " + HIS(TP) + " respect for the immortals sways "
	+ HIM(TP) + " otherwise.\n");
    return 1;
}
