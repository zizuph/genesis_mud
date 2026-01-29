/*
 *    Shire's standard inn by Igneous
 *
 *    Copyright (C) Chad Richardson Feb 97
 *
 *    An inhertable file used for rooms which contain an inn
 *    The main feature of this inn is the ability to buy for other
 *    players and your entire team if the player wishes to.
 *
 * 2016-01-24 - Cotillion
 * - Stop shop from cloning items to the void
 */
#pragma strict_types

inherit "/lib/trade";

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <money.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define MAX_PURCHASED 20        /* Maximum number of items we can buy. */

//  Prototypes
mixed * get_order(string order_name);

/*
 * Function name: cronfigure_shire_inn
 * Description:   Use this function to set up your inn trading.
 *                Add this function to your create_* function.
 */
void
configure_shire_inn()
{
    config_default_trade();  /* Set up the trading system */
    /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,    32,   2,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     4,   2,    1 })); /* Threshold */  
    if (TO->query_prop(ROOM_I_IS))
	TO->add_item("spittoon","You notice a small spittoon in the corner.\n");
}

/*
 * Function name: cronfigure_shire_inn
 * Description:   Use this function to set up the order and buy actions.
 *                Add this function in the init() function.
 */
void
init_shire_inn()
{
    add_action("do_order","order");
    add_action("do_order","buy");
}

/*
 * Function name: inn_hook_cant_pay
 * Description:   A hook to redefine if you want own message when player can't 
 *                pay the price.
 * Arguments:     price - The price he should had payed
 */
void
inn_hook_cant_pay(int price)
{
    write("You haven't got enough money to pay the price.\n");
}

/*
 * Function name: inn_hook_cant_carry
 * Description:   A hook to redefine if you want own message when player can't
 *                carry what he ordered.
 * Arguments:     ob - The object he couldn't carry
 *                player - the player who couldn't carry it
 */
void
inn_hook_cant_carry(object ob, object player)
{
    player->catch_msg("You are unable to carry "+LANG_THESHORT(ob)+".\n");
    ob->move(ENV(player));
}

/*
 * Function name: inn_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 *                player - The player recieving the order
 */
void
inn_hook_player_buys(object ob, string price, object *players)
{
    string comp_names;

    if (sizeof(players) == 1)
    {
	if (TP == players[0])
	{
	    write("You pay "+price+" and order yourself "+ob->short()+".\n");
	    say(QCTNAME(TP)+" orders "+HIM_HER(TP)+"self "+ob->short()+".\n");
	    return;
	}
    }

    comp_names = COMPOSITE_LIVE(players - ({TP}));

    write("You pay "+price+" and order "+ob->short()+" for "+comp_names+
      (member_array(TP,players) != -1 ? " as well as yourself" : "") +".\n");
    (players - ({TP}))->catch_msg(QTNAME(TP) + " buys you "+ob->short()+".\n");
    tell_room(TO,QCTNAME(TP)+" orders "+ob->short()+" for "+QCOMPLIVE+
      (member_array(TP,players) != -1 ? " as well as "+HIM_HER(TP)+"self" : "")+
      ".\n",players + ({TP}));
}

/*
 * Function name: inn_hook_ordered_too_many
 * Description  : Tells the player that he ordered too many items.
 * Arguments    : int num - the amount the player ordered.
 */
void
inn_hook_ordered_too_many(int num)
{
    write("You cannot buy more than " + MAX_PURCHASED +" items here.\n");
}

/*
 * Function name: inn_hook_no_player
 * Description  : Tells the player that we can't fin who is buying for.
 * Arguments    : name : The player we were trying to buy for
 */
void
inn_hook_no_player(string name)
{
    write(CAP(name)+" is not around for you to buy for.\n");
}
/*
 * Function name: inn_hook_no_item
 * Description  : Tells the player that there is no item of that type 
 * Arguments    : item - the item the player tried to order.
 */
void
inn_hook_no_item(string item)
{
    write("There is no "+item+" of that sort in stock.\n");
}

/*
 * Function name: do_order
 * Description  : Attmepts to figure out what the player ordered and what the
 *                player gets.
 * Arguments    : str - what the player told us to try and get.
 * Returns      : 1/0
 */
int
do_order(string str)
{
    object *players, order;
    string player_name, item_name, coin_pay_text, coin_get_text;
    string *words;
    int    *money_arr, amount, price, i;
    mixed temp;

    if (!str)
    {
	notify_fail(CAP(query_verb())+" what for whom?\n");
	return 0;
    }

    if (sscanf(str, "%s for %s", item_name, player_name) != 2)
    {
	player_name = TP->query_real_name();
	item_name = str;
    }

    words = explode(item_name, " ");
    if (sizeof(words) > 1)
    {
	sscanf(words[0], "%d", amount);
	if (amount > 0)
	    item_name = implode(words[1..sizeof(words)], " ");
	else
	    amount = 1;
    }
    else
	amount = 1;

    if (amount > MAX_PURCHASED)
    {
	inn_hook_ordered_too_many(amount);
	return 1;
    }

    players = FIND_STR_IN_OBJECT(player_name,TO);
    players = FILTER_PLAYERS(players);

    if (!sizeof(players))
    {
	if (player_name == "team" || player_name == "teammates")
	{
	    players = TP->query_team_others() + ({TP});
	    players = FILTER_PRESENT_LIVE(players);
	}
	else
	{
	    inn_hook_no_player(player_name);
	    return 1;
	}
    }


    temp = get_order(item_name);
    order = temp[0];
    price = temp[1];

    if (!order)
    {
	inn_hook_no_item(item_name);
	return 1;
    }

    player_name = lower_case(player_name);
    if (!order->query_prop(HEAP_I_IS) && amount != 1)
    {
	write("You are only able to buy one of "+LANG_THESHORT(order)+
	  " at a time.\n");
	// Clean up the objects we've cloned.
	order->remove_object();
	return 1;
    }
    else
	order->set_heap_size(amount);

    price = price * amount * sizeof(players);

    if (sizeof(money_arr = pay(price)) == 1)
    {
	// Clean up what we can't pay for
	inn_hook_cant_pay(price);
	order->remove_object();
	return 1;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));     
    inn_hook_player_buys(order,coin_pay_text,players);
    if (coin_get_text)
	write("You get " + coin_get_text + " back.\n");


    order->remove_object();
    for (i = 0; i < sizeof(players); i++)
    {
	order = get_order(item_name)[0];
	if (order->query_prop(HEAP_I_IS))
	    order->set_heap_size(amount);
	if (order->move(players[i]))
	{
	    inn_hook_cant_carry(order,players[i]);
	}
    }
    return 1;   
}

/*         !!IMPORTANT!!
 * 
 * This is an _example_ of the get_order function.  You _must_ redefine in
 * in your own inn file.  
 */

/*
 * Function name: get_order
 * Description:   gets the object the player ordered and returns it and
 *                the price of that object back to the do_order function.
 * Arguments:     order_name - what the player attempted to order.
 * Returns:       mixed array of 2 elements.
 *                [0]  order - The object the player ordered.
 *                [1]  price - What the object costs.
 */
mixed *
get_order(string order_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());

    switch(order_name)
    {
    case "beer":
	/*   Cloning the drink the easy way by using premade drink file.
	 *   I would prefer you make food and drink objects this way since
	 *   It is easier to find bugs and errors if they should arise.
	 *   -Igneous-
	 */
	order = clone_object("/d/Shire/igneous/obj/molson"); // The drink object
	price = 10;  // The price in copper coins
	break;
    case " blueberry muffin": case "muffin": case "muffins":
	//  Cloning the muffin the _long_ way by configuring /std/food
	order = clone_object("/std/food");
	order->set_name("muffin");
	order->set_adj(({"tasty","yummy","blueberry"}));
	order->set_short("blueberry muffin");
	order->set_pshort("blueberry muffins");
	order->set_long("A yummy looking blueberry muffin.\n");
	order->set_amount(100);    
	order->add_prop(HEAP_I_UNIT_VOLUME, 3);
	order->add_prop(HEAP_I_UNIT_WEIGHT, 5);
	order->add_prop(HEAP_I_UNIT_VALUE, 13);
	price = 13;  // The price in copper coins
	break;
    }

    return ({order, price});
}

