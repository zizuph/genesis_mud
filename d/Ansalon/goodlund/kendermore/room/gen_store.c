/* General Store of Kendermore, Gwyneth, June 1999 */
/* Taken from the General Shop of Vingaard Keep */
/* Modified from the General Shop in Calia by Maniac */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

inherit "/lib/shop";
inherit STREET_DESC;
inherit KENDERMORE_IN;

object keeper;

int
greed_buy()
{
    return 100;
}

greed_sell()
{
    return 100;
}

void
reset_kendermore_room()
{
    if (!objectp(keeper))
	{
            keeper = clone_object(KNPC + "netyle");
            keeper->move(TO);
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
    set_money_greed_buy("@@greed_buy@@");
    set_money_greed_sell("@@greed_sell@@");
    set_short("The general store of Kendermore");
    set_long("This is the General Store of Kendermore. There is a long " +
        "counter where the shopkeeper does all of his business. A sign " + 
        "has been firmly nailed down to the counter. There " + 
        "are no goods displayed, since they are all kept in the back " + 
        "room to prevent borrowing. The door to the east is propped " + 
        "open, showing the street outside.\n");
    add_item(({"ceiling","floor","wall"}),"It is made of wood.\n");
    add_item("walls","They are unadorned, and made with wood.\n");
    add_item("door", "It leads onto the street to the east.\n");
    add_item("counter", "The wooden counter is worn smooth from years " + 
        "of use.\n");
    add_item("street", "@@street_descr@@\n"); 
    add_item("sign", "The sign reads:\n\nYou may buy and sell items here.\n");

    add_prop(ROOM_M_NO_ATTACK, "@@no_attack");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "@@no_attack");

    set_store_room(KROOM + "gen_store2");
    add_invis_exit(KROOM + "gen_store2", "west", "@@wiz_check",);
    add_exit(KROOM + "street19", "east", 0);
    INSIDE;  /* This is a real room */
    query_store_room()->load_me();
    reset_kendermore_room();
}

string
no_attack()
{
    TP->add_prop(LIVE_S_EXTRA_SHORT, " spluttering furiously");

    tell_room(environment(TP), QCTNAME(TP) + " prepares to attack, " +
        "but out of nowhere a kender jumps in front of " + HIM(TP) +
        " and knocks " + HIS(TP) + " feet out from under " + HIM(TP) +
        "! " + C(HE(TP)) + " splutters furiously as " + HE(TP) + " tries " +
        "to reach " + HIS(TP) + " opponent, but the kender skips " +
        "away delighted with his prank.\n", TP);

    return "You prepare to attack, but out of nowhere a kender " +
        "jumps in front of you and knocks your feet out from " +
        "under you! You splutter furiously as you try to reach " +
        "your opponent, but he skips away from you delighted with " +
        "his prank.\n";
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

    if (TP->query_wiz_level())
	return 0;
    write("There is no obvious exit west.\n");
    return 1;
}

int
do_read(string str)
{
    if (str == "sign")
    {
	write("The sign reads:\n\nYou may buy and sell all items here.\n");
	return 1;
    }
    else
    {
	NF("Read what?    The sign?\n");
	return 0;
    }
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
    if (!P(keeper, TO))
    {
        NF("The shopkeeper is not here to buy your items.\n");
	return 0;
    }

    if (KMASTER->query_banished(this_player()->query_real_name()))
    {
        notify_fail("The shopkeeper won't deal with the likes of you!\n");
        return 0;
    }

    return ::do_sell(str);
}

int
do_buy(string str)
{
    if (!P(keeper, TO))
    {
        NF("The shopkeeper is not here to buy from.\n");
	return 0;
    }

    if (KMASTER->query_banished(this_player()->query_real_name()))
    {
        notify_fail("The shopkeeper won't deal with the likes of you!\n");
        return 0;
    }

    return ::do_buy(str);
}
