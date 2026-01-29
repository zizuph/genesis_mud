/*    Vendor in Kalaman    */
/* Taken from the General Shop of Vingaard Keep */
/* Modified from the General Shop in Calia by Maniac         */

// October 5th 2008, Navarre: Removing special non-sell prop
// I never saw a good reason for putting that restriction on
// buying/selling the armours.
// They are cluttering the streets, maybe now people will clean
// up.

#pragma save_binary

inherit "/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

inherit KALAMAN_IN;
inherit "/d/Ansalon/common/cheater";

#define STORE_ROOM CITY + "store_room1"

object keeper;

void
reset_kalaman_room()
{
    if (!keeper)
	if (!P(keeper, TO))
	{
	    keeper = clone_object(KNPC + "vendorman");
	    keeper->move(TO);
	}
}

/*
* Function name:   create_room
* Description:     Initialize this room
* Returns:
*/
void
create_kalaman_room()
{
    config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);
    set_short("Pawnbroker of Kalaman's market");
    set_long("This booth is the location of the local " +
      "pawnbroker of Kalaman's open-air market. " +
      "Made of some sort of purple canvas and held up " +
      "by strong wooden poles, this tent like structure " +
      "holds various items of interest. A small desk " +
      "sits in the middle of the booth with a sign on it.\n");
    add_item("sign","A sign. Read it.\n");
    add_item(({"canvas","purple canvas"}),
      "Purple canvas makes up most of this booth. How strange.\n");
    add_item(({"wooden poles","poles"}),
      "Wooden poles hold up the canvas.\n");
    add_item(({"items","item"}),
      "Various items of interest fill the booth. Perhaps you " +
      "should inquire about them?\n");
    add_item(({"small desk","desk"}),
      "A small desk with a sign on it sits in the middle of " +
      "the booth.\n");


    add_exit(CITY + "m9","out",0);
    set_store_room(STORE_ROOM);
    reset_kalaman_room();
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
	write("The sign reads:\n" +
              "     You may buy and sell items here.\n");
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

        //	if (ob[i]->query_prop(KALAMAN_NOBUY))
        //	{
        //	    shop_hook_sell_no_value(ob[i]);
        //	    continue;
        //	}

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
do_buy(string str)
{
    if (!keeper)
    {
        write("There's nobody here to buy from.\n");
        return 1;
    }

    if (check_cheater(this_player()))
        return 1;
    return ::do_buy(str);
}

int
do_sell(string str)
{
    if (!keeper)
    {
        write("There's nobody here to sell to.\n");
        return 1;
    }

    if (check_cheater(this_player()))
        return 1;
    return ::do_sell(str);
}
