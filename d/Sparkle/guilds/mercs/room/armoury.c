/* General Shop of Vingaard Keep by Morrigan, Jan 97      */
/* Modified from the General Shop in Calia by Maniac         */

#pragma save_binary

#include "../merc.h"
#include "room.h"

inherit "/lib/shop";
inherit "/std/room";

#define VK_NOBUY "_merc_guild_no_buy"
#define I_WAS_EVIL "_merc_guild_i_was_evil"
#define MERC_LORD_ARMOURY "_merc_lord_armoury"
#define MERC_LORD_ARMOURY_STEAL "_merc_lord_armour_i_stole"
#define MERC_ARMOURY "_merc_guild_armoury"
#define MAXLIST 100
#define MAX_HISTORY_EVENTS 10
#define MAX_NUMBER_PER_LORD(x) \
	(MCREST->query_number_followers(MCREST->query_members_lord(x->query_name())) + 1)
#define MIN_PRICE 1728
#define ASSIGN_AND_VALIDATE_STORE_OBJECT(s_o) \
    s_o = get_store_object(); \
    if (!(s_o)) \
    { \
        write("Error: no store object - please make a bug report.\n"); \
        return 1; \
    }

/* Format of history: 
 *    history = ([ "Capitalized Mercenary Lord Name" : 
 *                 ({ "first recorded event", "second recorded event", ...}), ])
 */

mapping history = ([ ]);

/* Format of bribes:
 *     bribes = ([ "reveal_item" : ({ "array of mercs", }),
 *		   "show_list"   : ({ "array of mercs", }),
 *		   "get_random_item" : ({ "array of mercs", })
 *		   "get_specific_item" : ({ "array of mercs", }) ])
 */

mapping bribes = ([ ]);

object keeper;
int shutdown_alarm = 0;

int
greed_buy()
{
    if (TP->query_wiz_level())
        return 100;

    if (IS_MERC_LORD(TP))
        return 130;
    else
        return 150;
}

greed_sell()
{
    if (IS_MERC_LORD(TP))
        return 130;
    else
        return 150;
}

int valid_user(object ob)
{
    string str = ob->query_name();

    if (ob->query_wiz_level())
	return 1;

    if (MCREST->query_lord_status(str) >= MERC_STATUS_LORD)
	return 1;

    if (MCREST->query_lord_status(MCREST->query_members_lord(str)) >=
	MERC_STATUS_LORD)
	return 1;

    return 0;
}

void
reset_room()
{
    /* Commenting this out. Corwin has left. (Gorboth)
    if (!keeper)
	if (!P(keeper, TO))
	{
	    keeper = clone_object(MNPC + "corwin");
            keeper->set_random_move(0);
	    keeper->move(TO);
	}
    */
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
    set_short("Mercenary Lord Armoury");
    set_long("Mercenary Lord Armoury. There is a sign.\n");
    set_store_room(MROOM + "armoury_store");
    add_exit(MROOM + "armoury_store", "west", "@@wiz_check", 0, 1);
    add_exit(MROOM + "lord_entrance", "east", 0);
    query_store_room()->load_me();
    reset_room();
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

void
shop_hook_sell_no_value(object ob)
{
    notify_fail(keeper->query_The_name(TP)+" says: "+LANG_THESHORT(ob)+" has "+
	"no value, why would you donate it?\n");
}

void
shop_hook_sell_worn_or_wielded(object ob)
{
    notify_fail(keeper->query_The_name(TP)+" says: You cannot donate worn or wielded objects.\n");
}

void
shop_hook_sell_no_sell(object ob, string str)
{
    if (stringp(str))
    {
        notify_fail(str);
    }
    else
    {
        notify_fail(keeper->query_The_name(TP)+" says: I don't want " + 
	    LANG_THESHORT(ob) + ".\n");
    }
}

void
shop_hook_list_empty_store(string str)
{
    notify_fail(keeper->query_The_name(TP)+" says: Your armoury is currently empty.\n");
}

int
shop_hook_list_no_match(string str)
{
    notify_fail(keeper->query_The_name(TP)+" says: There is no "+str+" in your armour.\n");
}

void
shop_hook_list_object(object ob, int price)
{
    string str, mess;

    str = sprintf("%-35s", capitalize(LANG_ASHORT(ob)));

    if (price < MIN_PRICE)
        price = MIN_PRICE;

    price = price * query_money_greed_buy() / 100;
    price = price / 144 * 144;

    if (ARMAGEDDON->shutdown_active())
        price = 0;

    if (mess = text(split_values(price)))
    {
        write(str + mess + ".\n");
    }
    else
    {
        write(str + "That item wouldn't cost you much.\n");
    }
}

int
shop_hook_sold_items(object *item)
{
    string lord = capitalize(MCREST->query_members_lord(TP->query_name()));
    int i;

    if (member_array(lord, m_indexes(history)) == -1)
    {
        history += ([ lord: ({ TP->query_name()+" donated "+
	    COMPOSITE_DEAD(item), }) ]);
    }
    else if (sizeof(history[lord]) < MAX_HISTORY_EVENTS)
    {
       history[lord] += ({ TP->query_name()+" donated "+
	    COMPOSITE_DEAD(item), });
    }
    else
    {
        history[lord] = history[lord][1..(MAX_HISTORY_EVENTS - 1)];
        history[lord] += ({ TP->query_name()+" donated "+
	    COMPOSITE_DEAD(item), });
    }

    write(break_string("You donated " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " donated " + QCOMPDEAD + ".\n");
    return 1;
}

int
shop_hook_bought_items(object *arr)
{
    string lord = capitalize(MCREST->query_members_lord(TP->query_name()));
    int i;

    if (member_array(lord, m_indexes(history)) == -1)
    {
        history += ([ lord: ({ TP->query_name()+" borrowed "+
	    COMPOSITE_DEAD(arr), }) ]);
    }
    else if (sizeof(history[lord]) < MAX_HISTORY_EVENTS)
    {
       history[lord] += ({ TP->query_name()+" borrowed "+
	    COMPOSITE_DEAD(arr), });
    }
    else
    {
        history[lord] = history[lord][1..(MAX_HISTORY_EVENTS - 1)];
        history[lord] += ({ TP->query_name()+" borrowed "+
	    COMPOSITE_DEAD(arr), });
    }

    write(break_string("You borrowed " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " borrowed " + QCOMPDEAD + ".\n");
    return 1;
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
    write("You cannot enter the store room.\n");
    say(QCTNAME(tp) + " tries to tries to enter the store room but fails.\n");
    return 1;
}

int
do_read(string str)
{
    if (str == "sign")
    {
	write("The sign reads:\n"+
	      "  Mercenary Lords and their followers may 'donate' and\n"+
	      "  'borrow' items here for the advancement of their cause.\n"+
	      "  They may also 'view' the most recent transactions of\n"+
	      "  their comrades.\n\n"+
          "It is now also possible to ask Corwin to enable transfers if " +
          "you want your causes equipment to be moved to the public " +
          "racks five minutes before the refreshing.\n\n" +
  	      "In fine print you read: Donating is free, borrowing is not.\n");
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
    keeper->command("shout That came from the racks! It will go back there!");
    keeper->command("emote snatches "+LANG_THESHORT(ob)+", and hands it to a "+
	"guard who leaves to the south, probably to place "+LANG_THESHORT(ob)+
	" back in the racks");
    tell_room(find_object(MROOM + "rack_room"), "A guard arrives and "+
	"drops a "+ob->short()+" on the ground here, mumbling something "+
	"under his breath before leaving.\n");
    ob->move(find_object(MROOM + "rack_room"));
}

object *
sell_it(object *ob, string str, int check)
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold, *all, *lord_list = ({ });
    object store = find_object(query_store_room()), destruct;
    mixed tmp;
    string lord = MCREST->query_members_lord(TP->query_name());

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    if (sizeof(ob) > 1)
    {
        keeper->command("say You can't donate all that at once! One at a "+
	    "time please.\n");
        return 0;
    }

    all = all_inventory(store);
    for (i=0;i<sizeof(all);i++)
        if (all[i]->query_prop(MERC_LORD_ARMOURY) == lord)
	    lord_list += ({ all[i] });

    for (i = 0; i < sizeof(ob); i++)
    {
        if (sizeof(all_inventory(ob[i])))
        {
	    notify_fail(keeper->query_The_name(TP)+" says: Empty that first "+
		"please.\n");
            continue;
        }

        if (ob[i]->query_prop(MERC_ARMOURY))
	{
            vk_nobuy_message(ob[i]);
            notify_fail("");
            continue;
        }

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

        /* Add prop */
        if (ob[i]->query_prop(MERC_LORD_ARMOURY))
            ob[i]->remove_prop(MERC_LORD_ARMOURY);

        ob[i]->add_prop(MERC_LORD_ARMOURY, lord);

        if (sizeof(lord_list) >= MAX_NUMBER_PER_LORD(TP) && 
	    MAX_NUMBER_PER_LORD(TP) != 0)
        {
            destruct = lord_list[(sizeof(lord_list) - 1)];

            keeper->command("emote claps his hands together and squeals with "+
		"delight.");
            keeper->command("asay excitedly You have exceeded your storage limit! "+
		"I'll still take this donation and place it in your armoury, but "+
	        "your "+destruct->short()+" will go to Maligant as tax!");
            lord_list -= ({ lord_list[(sizeof(lord_list) - 1)] });
            destruct->remove_object();
        }
    
        lord_list += ({ ob[i] });

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
	    if (j >= 1)
		break;
	    /*
	    * Only let people sell 20 objects at once and hopefully we wont get
	    * those too long evaluation problems.
	    */
	}
    }

    sold = sold - ({ 0 });

    return sold;
}

int
do_sell(string str)
{
    object *all, *lord_list = ({ });
    object store = find_object(query_store_room());
    string lord = MCREST->query_members_lord(TP->query_name());
    int playeralign, i;

    notify_fail("What?\n");
    if (query_verb() == "sell")
	return 0;

    NF("The shopkeeper is not here to assist you.\n");
    if (!P(keeper, TO))
	return 0;

    NF("The shopkeeper ignores your request.\n");
    if (!valid_user(TP))
	return 0;

    all = all_inventory(store);
    for (i=0;i<sizeof(all);i++)
        if (all[i]->query_prop(MERC_LORD_ARMOURY) == lord)
	    lord_list += ({ all[i], });

    NF("Nothing was donated.\n");
    return ::do_sell(str);
}

int do_value(string str)
{
    NF("What?\n");
    return 0;
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
    object store_object = get_store_object();
    mixed tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);
    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_buy(ob[i]))
            continue;

        if (ob[i]->query_prop(MERC_LORD_ARMOURY) != 
	    MCREST->query_members_lord(TP->query_name()))
	    continue;

/* We remove this so magic items can be borrowed */
//        if (tmp = ob[i]->query_prop(OBJ_M_NO_BUY))
//        {
//            shop_hook_buy_no_buy(ob[i], tmp);
//            continue;
//        }

        price = query_buy_price(ob[i]);

        if (price < MIN_PRICE)
            price = MIN_PRICE;

        if (ARMAGEDDON->shutdown_active())
	    price = 0;

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
            ob[i]->move(store_object, 1);
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
                ob[i]->move(store_object, 1);
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

int
do_buy(string str)
{
    object *item, *all = ({ }), *fil_item = ({ });
    int playeralign, i;
    string str1, str2, str3;
    object store_object;

    notify_fail("What?\n");
    if (query_verb() == "buy")
	return 0;

    NF("The shopkeeper is not here to assist you.\n");
    if (!P(keeper, TO))
	return 0;

    NF("The shopkeeper ignores your request.\n");
    if (!valid_user(TP))
	return 0;

    NF("Borrow what?\n");
    if (!strlen(str))
        return 0;

    ASSIGN_AND_VALIDATE_STORE_OBJECT(store_object);

    all = all_inventory(find_object(query_store_room()));

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

    for (i=0;i<sizeof(all);i++)
        if (all[i]->query_prop(MERC_LORD_ARMOURY) == 
	    MCREST->query_members_lord(TP->query_name()))
        fil_item += ({ all[i] });
 
    item = FIND_STR_IN_ARR(str1, fil_item);

    if (!sizeof(item))
        return shop_hook_buy_no_match(str1);

    if (!sizeof(item))
    {
        return shop_hook_buy_no_match(str1);
    }

    item = buy_it(item, str2, str3);

    if (sizeof(item))
    {
        return shop_hook_bought_items(item);
    }

    return 0; /* Player tried to sell a non sellable object. */
}

int wiz_list(string str)
{
    object *item_arr = ({ });
    object store_object;
    string name;
    int i;

    ASSIGN_AND_VALIDATE_STORE_OBJECT(store_object);

    NF("What?\n");
    if (!TP->query_wiz_level())
	return 0;

    item_arr = all_inventory(store_object);

    write("Contents of the armoury:\n");

    for (i=0;i<sizeof(item_arr);i++)
    {
        name = "("+item_arr[i]->query_prop(MERC_LORD_ARMOURY)+")";

        write(sprintf(" - %-35s : %-15s", item_arr[i]->short(), name)+"\n");
    }

    return 1;
}

int
do_list(string str)
{
    object *tmp_items;
    object *item_arr = ({ });
    object store_object;
    int i, max, price, *arr;

    notify_fail("The shopkeeper ignores your request.\n");
    if (!valid_user(TP))
	return 0;

    ASSIGN_AND_VALIDATE_STORE_OBJECT(store_object);

    tmp_items = all_inventory(store_object);

    for (i=0;i<sizeof(tmp_items);i++)
    {
        if (tmp_items[i]->query_prop(MERC_LORD_ARMOURY) == 
		MCREST->query_members_lord(TP->query_name()))
            item_arr += ({ tmp_items[i], });
    }

    if (TP->query_wiz_level())
        item_arr = tmp_items;

    if (!sizeof(item_arr))
    {
        shop_hook_list_empty_store(str);
        return 0;
    }

    if (str == "weapons")
    {
        item_arr = filter(item_arr, weapon_filter);
    }
    else if (str == "armours")
    {
        item_arr = filter(item_arr, armour_filter);
    }
    else if (str)
    {
        item_arr = FIND_STR_IN_ARR(str, item_arr);
    }

    if (sizeof(item_arr) < 1)
        return shop_hook_list_no_match(str);
 
    max = MIN(MAXLIST, sizeof(item_arr));

    write(keeper->query_The_name(TP)+" says: You currently have the "+
        "following items in your armoury.\n");

    for (i = 0; i < max; i++)
    {
        price = query_buy_price(item_arr[i]);
        shop_hook_list_object(item_arr[i], price);
    }

    write(keeper->query_The_name(TP)+" says: You have stored "+sizeof(item_arr)+
       " of a maximum "+MAX_NUMBER_PER_LORD(TP)+" items.\n");


    if (max < sizeof(item_arr))
    {
        write("Truncated...\n");
    }

    return 1;
}

public int
list_history(string str)
{
    string lord = capitalize(MCREST->query_members_lord(TP->query_name()));
    int i;

    notify_fail("The shopkeeper ignores your request.\n");
    if (!valid_user(TP))
	return 0;

    NF("Just list! Or list transactions or history.\n");
    if (str && str != "transactions" && str != "history")
        return 0;

    if (member_array(lord, m_indexes(history)) == -1)
    {
        keeper->command("emote retrieves his book and flips through the pages.");
        keeper->command("say I see no transactions on record for "+lord+
	    "'s cause.");
        return 1;
    }

    keeper->command("emote retrieves his book and flips through the pages.");
    keeper->command("say Ahh yes, I have some recorded activity. This is "+
	"what my transaction log shows.");

    for (i=0;i<sizeof(history[lord]);i++)
        keeper->command("say "+history[lord][i]);
    return 1;
}

/* Function name: do_show
 * Description  : Allow the player to appraise one of the objects in stock.
 * Returns      : int - 1/0 - true if success.
 * Arguments    : string str - the name of the objects to search for.
 */
int
do_show(string str)
{
    object *tmp_items, *item_arr;
    object store_object;
    int i, *arr;

    ASSIGN_AND_VALIDATE_STORE_OBJECT(store_object);

    tmp_items = all_inventory(store_object);
    item_arr = ({ });

    for (i=0;i<sizeof(tmp_items);i++)
    {
        if (tmp_items[i]->query_prop(MERC_LORD_ARMOURY) == 
		MCREST->query_members_lord(TP->query_name()))
            item_arr += ({ tmp_items[i], });
    }

    if (TP->query_wiz_level())
        item_arr = tmp_items;

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

void init_shop()
{
    ::init_shop();

    add_action("list_history", "view");
    add_action("do_show", "show");
    add_action("do_buy", "borrow");
    add_action("do_sell", "donate");
    add_action("request_item", "request");
    add_action("wiz_list", "wlist");
}

/* Add bribe functions here, called by the keeper npc */
int reveal_item(object ob)
{
    object *all = all_inventory(find_object(query_store_room()));
    object *items = ({ });
    string lord = MCREST->query_members_lord(ob->query_name());
    int i;

    if (member_array(ob->query_name(), bribes["reveal_item"]) != -1)
    {
        keeper->command("whisper "+ ob->query_name()+" If you want more, you "+
	    "have to give more!");
        return 1;
    }

    for (i=0;i<sizeof(all);i++)
    {
        if (all[i]->query_prop(MERC_LORD_ARMOURY) != lord)
            items += ({ all[i] });
    }

    if (!sizeof(bribes["reveal_item"]))
        bribes["reveal_item"] = ({ ob->query_name() });
       else
        bribes["reveal_item"] += ({ ob->query_name() });

    if (!sizeof(items))
    {
        keeper->command("whisper "+ob->query_name()+" It doesn't look like "+
	    "any of the other lords have anything stored right now.");
        write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " corwin: " +
        ob->query_name() + " bribed for reveal_item (failed)\n");
        return 1;
    }

    i = random(sizeof(items));

    keeper->command("whisper "+ob->query_name()+" Okay, listen. It looks like "+
	"someone from "+items[i]->query_prop(MERC_LORD_ARMOURY)+"'s group "+
	"has a "+items[i]->short()+" in storage. That's all I can say.");
    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " corwin: " +
        ob->query_name() + " bribed for reveal_item ("+
	items[i]->short()+"/"+items[i]->query_prop(MERC_LORD_ARMOURY)+")\n");

    return 1;
}

int show_list(object ob)
{
    string *all = m_indexes(history);
    string lord = MCREST->query_members_lord(ob->query_name());
    int i;

    if (member_array(ob->query_name(), bribes["show_list"]) != -1)
    {
        keeper->command("whisper "+ ob->query_name()+" If you want more, you "+
	    "have to give more!");
        return 1;
    }

    if (member_array(lord, all))
        all -= ({ lord });

    if (!sizeof(bribes["show_list"]))
        bribes["show_list"] = ({ ob->query_name() });
       else
        bribes["show_list"] += ({ ob->query_name() });

    if (!sizeof(all))
    {
        keeper->command("whisper "+ob->query_name()+" It doesn't look like any "+
	    "of the other lords have stored anything right now. Come back later!");
        write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " corwin: " +
            ob->query_name() + " bribed for show_list (failed)\n");
	return 1;
    }

    i = random(sizeof(all));
    lord = all[i];

    keeper->command("emote retrieves his book and flips through the pages.");
    keeper->command("whisper "+ob->query_name()+" Ahh yes, I have some recorded "+
	"activity for "+lord+". This is "+
	"what my transaction log shows.");

    for (i=0;i<sizeof(history[lord]);i++)
        keeper->command("whisper "+ob->query_name()+" "+history[lord][i]);

    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " corwin: " +
        ob->query_name() + " bribed for show_list ("+lord+")\n");

    return 1;
}

int get_random_item(object ob)
{
    object *all = all_inventory(find_object(query_store_room()));
    object *items = ({ });
    string lord = MCREST->query_members_lord(ob->query_name());
    int i;

    if (member_array(ob->query_name(), bribes["get_random_item"]) != -1)
    {
        keeper->command("whisper "+ ob->query_name()+" If you want more, you "+
	    "have to give more!");
        return 1;
    }

    for (i=0;i<sizeof(all);i++)
    {
        if (all[i]->query_prop(MERC_LORD_ARMOURY) != lord)
            items += ({ all[i] });
    }

    if (!sizeof(bribes["get_random_item"]))
        bribes["get_random_item"] = ({ ob->query_name() });
       else
        bribes["get_random_item"] += ({ ob->query_name() });

    if (!sizeof(items))
    {
        keeper->command("emote ducks back into the storage room briefly.");
        keeper->command("whisper "+ob->query_name()+" There's nothing back "+
	    "to give you right now, come back later!");
        write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " corwin: " +
            ob->query_name() + " bribed for get_random_item (failed)\n");
        return 1;
    }

    i = random(sizeof(items));

    keeper->command("emote ducks back into the storage room briefly.");
    keeper->command("whisper "+ob->query_name()+" Here, take this, and don't "+
	"tell anyone I gave it to you! I think someone in "+
        items[i]->query_prop(MERC_LORD_ARMOURY)+"'s group donated it.");
    ob->catch_tell(keeper->query_The_name(ob)+" slips you something "+
	"surreptitiously.\n");

    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " corwin: " +
        ob->query_name() + " bribed get_random_item ("+
	items[i]->short()+"/"+items[i]->query_prop(MERC_LORD_ARMOURY)+")\n");

    items[i]->move(ob);
    return 1;
}

int get_specific_item(object ob)
{
    if (ob->query_prop(MERC_LORD_ARMOURY_STEAL) > 1)
    {
        keeper->command("whisper "+ob->query_name()+" I already gave you something! "+
	    "Get out of here before you get me into trouble!");
        return 1;
    }

    if (member_array(ob->query_name(), bribes["get_specific_item"]) != -1)
    {
        keeper->command("whisper "+ ob->query_name()+" If you want more, you "+
	    "have to give more!");
        return 1;
    }

    if (!ob->query_prop(MERC_LORD_ARMOURY_STEAL))
        ob->add_prop(MERC_LORD_ARMOURY_STEAL, 1);

    if (!sizeof(bribes["get_specific_item"]))
        bribes["get_specific_item"] = ({ ob->query_name() });
       else
        bribes["get_specific_item"] += ({ ob->query_name() });

    keeper->command("whisper "+ob->query_name()+" Okay, here's the deal. You can "+
	"<request> an item. If its there, its yours. If not, you're out of luck. "+
	"I can't let you try more than once, this is too risky!");
    return 1;
}

int request_item(string str)
{
    object *all = all_inventory(find_object(query_store_room()));
    object *it, *items = ({ });
    string lord = MCREST->query_members_lord(TP->query_name());
    int i;

    notify_fail("What?\n");
    if (TP->query_prop(MERC_LORD_ARMOURY_STEAL) != 1)
        return 0;

    for (i=0;i<sizeof(all);i++)
    {
        if (all[i]->query_prop(MERC_LORD_ARMOURY) != lord)
            items += ({ all[i] });
    }

    it = FIND_STR_IN_ARR(str, items);

    if (!sizeof(it))
    {
        keeper->command("whisper "+TP->query_name()+" Sorry but you lose. There's "+
	    "no such item, now get lost before you get us both killed!");

        write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " corwin: " +
            TP->query_name() + " bribed for get_specific_item (failed)\n");

        TP->add_prop(MERC_LORD_ARMOURY_STEAL, 2);
        return 1;
    }

    keeper->command("whisper "+TP->query_name()+" It's your lucky day, I found "+
	"a "+it[0]->short()+" back there for you. I think it was donated by "+
	"someone from "+it[0]->query_prop(MERC_LORD_ARMOURY)+"'s group. "+
	"Don't tell anyone about this, "+
	"or you will be risking both our necks! Go away, hurry!");
    TP->catch_tell(keeper->query_The_name(TP)+" slips you something "+
	"surreptitiously.\n");
    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " corwin: " +
        TP->query_name() + " bribed for get_specific_item ("+
	it[0]->short()+"/"+it[0]->query_prop(MERC_LORD_ARMOURY)+")\n");

    TP->add_prop(MERC_LORD_ARMOURY_STEAL, 2);
    it[0]->move(TP);
    return 1;
}

void wiz_tell(object ob)
{
        ob->catch_tell("As a wizard, you may use 'wlist' to view all "+
	    "contents of the armoury, and whose cause has claim to them.\n");
}

void enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->query_wiz_level())
        set_alarm(1.0, 0.0, "wiz_tell", ob);
}

void armageddon_transfer()
{
    object *item_arr = ({ }), *armours = ({}), *weapons = ({}), *others = ({});
    object store_object, container;
    string name;
    int i;

    if (!ARMAGEDDON->shutdown_active()) 
    {
        find_living("eowul")->catch_msg("Shutdown thingy called without shutdown active.\n");
        return;
    }

    store_object = find_object(query_store_room());
    item_arr = all_inventory(store_object);

    for (i=0;i<sizeof(item_arr);i++)
    {
        name = item_arr[i]->query_prop(MERC_LORD_ARMOURY);
        if(MCREST->query_private_rack_transfer(name))
        {
            if(IS_ARMOUR_OBJECT(item_arr[i]))
            {
                armours += ({ item_arr[i] });
            }
            else if(IS_WEAPON_OBJECT(item_arr[i]))
            {
                weapons += ({ item_arr[i] });
            }
            else
            {
                others += ({ item_arr[i] });
            }
        }
    }

    if(sizeof(others) || sizeof(armours) || sizeof(weapons))
    {
        keeper->command("emote leaves for a moment to take some equipment " +
            "to the public racks and then returns again.");

        // Load the rack room
        (MROOM + "rack_room")->teleledningsanka();

        // Move the armours
        if(sizeof(armours))
        {
            container = present("_merc_guild_armour_rack_", 
                find_object((MROOM + "rack_room")));

            if(objectp(container))
            {
                tell_room(find_object((MROOM + "rack_room")),
                    "Corwin enters and places " + COMPOSITE_DEAD(armours) + 
                    " in the " + QSHORT(container) + ".\n");
                armours->move(container);
            }
        }

        // Move the weapons
        if(sizeof(weapons))
        {
            container = present("_merc_guild_weapon_rack_", 
                find_object((MROOM + "rack_room")));

            if(objectp(container))
            {
                tell_room(find_object((MROOM + "rack_room")),
                    "Corwin enters and places " + COMPOSITE_DEAD(weapons) + 
                    " in the " + QSHORT(container) + ".\n");
                weapons->move(container);
            }
        }

        // Move the weapons
        if(sizeof(others))
        {
            container = present("_merc_guild_junk_box_", 
                find_object((MROOM + "rack_room")));

            if(objectp(container))
            {
                tell_room(find_object((MROOM + "rack_room")),
                    "Corwin enters and places " + COMPOSITE_DEAD(others) + 
                    " in the " + QSHORT(container) + ".\n");
                others->move(container);
            }
        }
    }

    find_living("eowul")->catch_msg(sprintf("Moved armours: %O, moved weapons: %O, moved others: %O\n", armours, weapons, others));
}

void start_armageddon_alarm()
{
    int delay;

    delay = ARMAGEDDON->query_delay() - 300;
    if(delay < 0)
        delay = ARMAGEDDON->query_delay();

    shutdown_alarm = set_alarm(itof(delay), 0.0, armageddon_transfer);
}

void stop_armageddon_alarm()
{
    if(shutdown_alarm)
        remove_alarm(shutdown_alarm);

    shutdown_alarm = 0;
}
