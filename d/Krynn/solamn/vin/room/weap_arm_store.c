/* General Shop of Vingaard Keep by Morrigan, Jan 97      */
/* Modified from the General Shop in Calia by Maniac         */
/*
 * Louie April 2006 - Set greed to 100.
 */

#pragma save_binary

inherit "/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include "../knight/guild.h"

inherit IN_BASE;

object keeper, box;

int
greed_buy()
{
    if (MEMBER(TP))
	return 75;
    else
	return 100;
}

greed_sell()
{
    if (MEMBER(TP))
	return 81;
    else
	return 100;
}

void
reset_vin_room()
{
    if (!keeper)
	if (!P(keeper, TO))
	{
	    keeper = clone_object(VNPC + "darren");
	    keeper->move(TO);
	}
    if (!box)
    {
	box = clone_object(VOBJ + "charitybox");
	box->move(TO);
    }
}

/*
* Function name:   create_room
* Description:     Initialize this room
* Returns:
*/
void
create_room()
{
    config_default_trade();
/*
    set_money_greed_buy("@@greed_buy@@");
    set_money_greed_sell("@@greed_sell@@");
*/
    set_money_greed_buy(100);
    set_money_greed_sell(100);
    set_short("Arms, Armour, and General Supply Store");
    set_long("This is the Vingaard Keep Arms, Armour and " +
      "General Supply Store, a well-used establishment in " +
      "northern Solamnia. A broad counter spreads across the room " +
      "and a sign hangs from the ceiling. In a far corner of " +
      "the store is an oil-burning lamp. The store has an exit " +
      "south back to the street.\n");
    AI(({"ceiling","floor","wall"}),"It is composed of granite blocks.\n");
    AI("walls","They are composed of granite blocks.\n");
    AI(({"blocks","granite","granite blocks"}),"They are made of carved " +
      "volcanic rock.\n");
    AI(({"counter","broad counter"}),"The counter is scuffed, due to the " +
      "heavy amount of transactions that occur.\n");
    AI(({"oil-burning lamp","lamp"}),"The lamp hangs from a chain in the " +
      "ceiling.\n");
    AI("street","The street is the very same one that encircles Vingaard " +
      "Keep.\n");
    AI("chain","The chain is embedded in the rock of the ceiling.\n");
    set_store_room(VROOM + "weap_arm_store2");
    AE(VROOM + "weap_arm_store2", "north", "@@wiz_check", 0, 1);
    AE(VROOM + "ss3", "south", 0);
    INSIDE;  /* This is a real room */
    query_store_room()->load_me();
    reset_vin_room();
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
    object tp;

    tp = TP;
    if (tp->query_wiz_level())
	return 0;
    write("Some magic force keeps you from going north.\n");
    say(QCTNAME(tp) + " tries to go north but fails.\n");
    return 1;
}

int
do_read(string str)
{
    if (str == "sign")
    {
	write("The sign reads:\nYou may buy and sell all items here.\n");
	return 1;
    }
    else
    {
	NF("Read what?    The sign?\n");
	return 0;
    }
}

void
vk_nobuy_message(object ob)
{
    notify_fail(QCTNAME(keeper)+" shouts: You bastard! and begins to beat "+
      "you with "+LANG_THESHORT(ob)+"!\n");
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
    int playeralign;

    NF("The shopkeeper is not here to buy your items.\n");
    if (!P(keeper, TO))
	return 0;
    NF("The shopkeeper says: I will not buy from those such as you!\n");
    playeralign = TP->query_alignment();
    if (playeralign < 0)
    {
	if (!TP->query_prop(I_WAS_EVIL))
	    TP->add_prop(I_WAS_EVIL, 1);
    }
    NF("The shopkeeper says: I will not buy from those such as you!\n");
    if (TP->query_prop(I_WAS_EVIL))
	return 0;

    return ::do_sell(str);
}

int
do_buy(string str)
{
    int playeralign;

    NF("The shopkeeper is not here to buy from.\n");
    if (!P(keeper, TO))
	return 0;
    NF("The shopkeeper says: I will not sell to those such as you!\n");
    playeralign = TP->query_alignment();
    if (playeralign < 0)
    {
	if (!TP->query_prop(I_WAS_EVIL))
	    TP->add_prop(I_WAS_EVIL, 1);
    }
    NF("The shopkeeper says: I will not sell to those such as you!\n");
    if (TP->query_prop(I_WAS_EVIL))
	return 0;

    return ::do_buy(str);
}
