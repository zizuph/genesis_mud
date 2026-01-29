/*
 *  The standard shop of the Emerald Domain
 *
 *  This file is copied from /d/Gondor/common/lib/shop which
 *  was created by Olorin in 1994. 
 * 
 *  Features that differ from /d/Genesis/lib/shop:
 *  - Shopkeeper
 *  - Check for special items that are not bought
 *  - greed is set using VBFC discriminate()
 *
 *  Gorboth, July 2003
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/d/Genesis/lib/shop";

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define MAXLIST 30
#define MONEY_TYPE ({ "cc", "sc", "gc", "pc" })
#define SHOP_TMP_WANT_NO_BUSINESS "_want_no_business"

/*
 *	Prototypes
 */
static string  exa_poster();
public void    reset_room();
public void    shop_hook_no_business(object pl);
public void    remove_tmp_want_no_business(object pl);

/*
 *	Global variables
 */
static object  keeper;
static string *enemies = ({}),
              *hated_race,
              *suspected_race,
              *favoured_race,
               keeper_file,
              *no_sell_prop,
               shop_name;

public void set_keeper_file(string str) { keeper_file = str; }

public void
set_no_sell_prop(mixed str)
{
    if (stringp(str))
        no_sell_prop = ({ str });
    else if (pointerp(str))
        no_sell_prop = str;
}

void set_shop_name(string str) { shop_name = str; }
void set_hated_race(string *arr) { hated_race = arr; }
void set_suspected_race(string *arr) { suspected_race = arr; }
void set_favoured_race(string *arr) { favoured_race = arr; }

/*
 * Function name:   create_shop
 * Description:     Initialize the shop room
 */
public void
create_shop()
{
    set_long("The standard shop of the Emerald Domain.\n");
    set_short("A shop");
    set_store_room("/d/Emerald/lib/store");
    set_shop_name("Emerald's Standard Shop");
// CHANGE THE FOLLOWING LINE
    set_keeper_file("/d/Emerald/telberin/npc/telberin_elf");
    set_no_sell_prop("_Emerald_no_sell");
}

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
nomask void
create_emerald_room()
{
    config_default_trade();  /* Set up the trading system */

    set_money_give_max(1000);
    set_money_give_out(   ({ 10000,   700,  40,    1 }));
    set_money_give_reduce(({     0,     4,   3,    9 }));
    set_money_greed_sell("@@discriminate");
    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");

    add_item(({"item","items"}), BSN(
        "There are numerous items lying about. You will need to check the"
      + " pricelist to get an idea of what, specifically, you wish to"
      + " purchase here."));

    add_item(({"owner","store owner"}), BSN(
        "The store owner is mostly going about the business at hand,"
      + " but keeps a watchful eye in your direction to make sure that"
      + " nothing accidentally makes its way into your posession without"
      + " proper payment."));

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    create_shop();

    add_item(({"sign", "poster","list","prices"}), exa_poster());
    add_cmd_item(({"sign", "poster","list","prices"}), "read", exa_poster());

    enable_reset(200);
    reset_room();
}

int
do_read(string str)
{
    return 0;
}

static string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy sword for gold and get copper back\n"
      + "    buy sword for gold coins\n"
      + "    sell sword for copper coins\n"
      + "    sell all  - will let you sell all items except for\n"
      + "                worn and wielded ones.\n"
      + "    sell sword, sell second sword, sell sword 2, sell two swords\n"
      + "                also works. You might want to change the verb to\n"
      + "                'value' or 'buy' too.\n"
      + "    If you want a list of all swords available in the store, the\n"
      + "    correct syntax is: 'list swords'.\n"
      + "\n";
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
public void
init()
{
    ::init();
    init_shop();
}

public void
fix_keeper()
{
    keeper = clone_object(keeper_file);
    keeper->arm_me();
    keeper->move_living("down", TO);
}

public void
reset_room()
{
    if (!objectp(keeper))
        fix_keeper();
}

public mixed
check_keeper()
{
    object  enemy;
    if (keeper && present(keeper,TO))
    {
        if (enemy = keeper->query_attack())
        {
            if(enemy == TP)
                NF("The shopkeeper is trying to kill you, so you cannot do that!\n");
            else
                NF("The shopkeeper is busy fighting, so you cannot do that!\n");
            return 0;
        }
        else 
            return 1;
    }
    else
    {
        NF("There is no shopkeeper here, so you cannot do that!\n");
        return 0;
    }
}

int
query_shop_no_business(mixed pl)
{
    return 0;
}

public int
do_buy(string args)
{
    if (check_keeper())
    {
        if (query_shop_no_business(TP))
        {
            shop_hook_no_business(TP);
            return 0;
        }
        return ::do_buy(args);
    }
    return 0;
}

public int
do_value(string args)
{
    if (check_keeper())
    {
        if (query_shop_no_business(TP))
        {
            shop_hook_no_business(TP);
            return 0;
        }
        return ::do_value(args);
    }
    return 0;
}

public int
do_sell(string args)
{
    if (check_keeper())
    {
        if (query_shop_no_business(TP))
        {
            shop_hook_no_business(TP);
            return 0;
        }
        return ::do_sell(args);
    }
    return 0;
}

public int
do_list(string args)
{
    if (check_keeper())
        return ::do_list(args);
    return 0;
}

public int
shop_hook_sell_no_match(string str)
{
    NF("The shopkeeper says: You don't have any " + str + ".\n");
    return 0;
}

public int
shop_hook_sold_nothing()
{
    if (!TP->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
        NF("The shopkeeper says: You didn't have much to sell.\n");
    return 0;
}

public void
shop_hook_sell_no_value(object ob)
{
    if (ob->id("ctower_torque"))
    {
        NF("The shopkeeper says: That is worth more than everything in"
         + " this shop combined! I simply cannot afford it.\n");
        return;
    }

    NF("The shopkeeper says: "+CAP(LANG_THESHORT(ob))+" is worthless.\n");
}

public void
shop_hook_sell_no_sell(object ob, string str)
{
    if (stringp(str))
        NF(str);
    else
        NF("The shopkeeper says: I don't buy such items.\n");
}

public void
shop_hook_sell_object_stuck(object ob, int err)
{
    NF("The shopkeeper says: It seems you are stuck with that.\n");
}

public void
shop_hook_sell_get_money(string str)
{
    write("The shopkeeper gives you " + str + ".\n");
}

public void
shop_hook_buy_no_match(string str)
{
    NF("The shopkeeper says: I have no " + str + " to sell.\n");
}

public void
shop_hook_cant_carry(object ob, int err)
{
    NF("You drop " + LANG_THESHORT(ob) + " on the floor.\n" +
       "The shopkeeper says: You can't carry more, I'm afraid.\n");
}

public void
shop_hook_buy_magic_money(object ob)
{
    keeper->command("say You are carrying magic money my friend, " +
        "no deal!\n");
}

public void
shop_hook_buy_pay_money(string str, string change)
{
    write("You give " + str + " to the shopkeeper.\n");
    if (change)
        write(CAP(PRONOUN(keeper)) + " gives you " + change + " back.\n");
}

public void
shop_hook_value_not_interesting(object ob)
{
    if (!TP->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
        NF("The shopkeeper says: That item doesn't interest me.\n");
    else
        NF("");
}

public void
shop_hook_value_held(object ob, string text)
{
    keeper->command("say I could offer about " + text +
        " for your " + ob->short() + ".");
}

public void
shop_hook_value_store(object ob, string text)
{
    keeper->command("say I value " + LANG_THESHORT(ob) +
        " to " + text + ".");
}

public void
shop_hook_value_asking(string str)
{
    say(QCTNAME(TP)+" asks "+QTNAME(keeper) +
        " about the value of the "+str+".\n");
}

public int
shop_hook_value_no_match(string str)
{
    NF("The shopkeeper says: We hold no '" + str + "' in stock.\n");
}

public void
shop_hook_list_empty_store(string str)
{
    NF("The shopkeeper says: We are currently sold out.\n");
}

public int
shop_hook_list_no_match(string str)
{
    NF("The shopkeeper says: We have no '" + str + "' in stock.\n");
}

/* 
 * The idea for this routine is got from Padermud. --Randor
 */
public mixed
neat_text(int *arr)
{
    int     i,
            num = sizeof(query_money_types());
    string  temp;

    if (sizeof(arr) < num) /* invalid array */
        return;

    temp = "";
    for (i = num - 1; i >= 0; i--)
    {
        if (arr[i] > 0)
            temp += sprintf("%2d %2s ", arr[i], MONEY_TYPE[i]);
        else
            temp += "      ";
    }
    return temp;
}

public void
shop_hook_list_object(object ob, int price)
{
    string  str,
            mess;
    mess = neat_text(split_values(price));
    if (!stringp(mess))
        mess = "That item wouldn't cost you much.\n";
    write(BSN(sprintf("%-35s %20s", capitalize(LANG_ASHORT(ob)), mess)));
}

public void
remove_tmp_want_no_business(object pl)
{
    pl->remove_prop(SHOP_TMP_WANT_NO_BUSINESS);
}

/*
 * Function name:    shop_hook_filter_sell
 * Description:      Default filter function
 *                   Checks if player can sell item to shop
 *                   Default buys everything but weapons and armours
 * Argument:         object ob - the object to check
 * Returns:          The fail message or 1 if shop does not buy,
 *                   0 else
 */
public mixed
shop_hook_filter_sell(object x)
{
    if (weapon_filter(x) || armour_filter(x))
        return "The shopkeeper says: I do not want your " + x->short() + "!\n" +
               "The shopkeeper says: I do not trade in weapons or armours!\n";
    else
        return 0;
}

public void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("say Where did you get this " +
        ob->short() + "?");
    keeper->command("glare " + pl->query_real_name());
    keeper->command("say I can't imagine you came by such things honorably!");
    keeper->command("say Leave before I call the guards!");
}

public void
shop_hook_no_business(object pl)
{
    keeper->command("say I do not want your business, " +
        (pl->query_gender() ? "Lady" : "Mister") + "!");
    keeper->command("spit " + pl->query_real_name());
    keeper->command("say Leave before I call the guards!");
}

/*
 * Function name: shop_hook_allow_sell
 * Description:	  If you want to do more testing on objects 
 *                the player intend to sell.
 * Argument:	  ob - The object player wants to sell
 * Returns:	  1 if we allow player to sell the object (default)
 */
public int
shop_hook_allow_sell(object ob)
{
    int     i;
    mixed   prop = 0,
            test,
            msg;
    object  pl = TP;
    string  name = pl->query_name();


    if ((msg = shop_hook_filter_sell(ob)))
    {
        if (stringp(msg))
            NF(msg);
        else
            NF("The shopkeeper says: I do not want your " + ob->short() + "!\n");
        return 0;
    }

    NF("");
    if (member_array(name, enemies) > -1)
    {
        if (pl->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
            return 0;
        TO->shop_hook_no_business(pl);
        pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
        set_alarm(0.0, 0.0, &remove_tmp_want_no_business(pl));
        return 0;
    }

    for (i = 0; i < sizeof(no_sell_prop); i++)
    {
        if ((test = ob->query_prop(no_sell_prop[i])))
            prop = test;
    }

    if (!prop)
        return 1;

    if (stringp(prop))
        write(prop);
    else if (intp(prop) && query_verb() != "value")
        TO->shop_hook_stolen_item(pl, ob);
    else
        return 1;

    pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
    set_alarm(0.0, 0.0, &remove_tmp_want_no_business(pl));

    enemies += ({ name });
    return 0;
}

/*
 * Function name: shop_hook_allow_buy
 * Description:   A hook to use if you want to test the object 
 *		  further if you allow it to be bought
 * Arguments:	  ob - The object player wants to buy.
 * Returns:	  1 if we allow it to be bought (default)
 */
public int
shop_hook_allow_buy(object ob)
{
    object  pl = TP;
    string  name = pl->query_name();

    NF("");
    if (member_array(name, enemies) > -1)
    {
        if (pl->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
            return 0;
        TO->shop_hook_no_business(pl);
        pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
        set_alarm(0.0, 0.0, &remove_tmp_want_no_business(pl));
        return 0;
    }

    return 1;
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
public int 
wiz_check()
{
    seteuid(geteuid(TO));
    if (TP->query_wiz_level())
        return 0;
    if(check_keeper())
    {
        write("The owner of the store keeps you from going there.\n");
        say("The owner of the store blocks " + QTNAME(TP) + ".\n");
    }
    else
    {
        write("Some magic force keeps you from going there.\n");
        say(QCTNAME(TP) + " tries to enter the storeroom but fails.\n");
    }
    return 1;
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
public int
discriminate()
{
    object  tp = TP;
    string  race = tp->query_race();
    int     bargain = tp->query_skill(SS_TRADING);

    if (bargain > 30) 
        bargain = 30;
    bargain = 115 - bargain;

    if (member_array(race, hated_race) > -1)
        bargain = (bargain * 120) / 100;
    else if (member_array(race, suspected_race) > -1)
        bargain = (bargain * 110) / 100;
    else if (member_array(race, favoured_race) > -1)
        bargain = (bargain * 90) / 100;
    return bargain;
}

/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:	  An array with the objects sold
 */
public object *
sell_it(object *ob, string str, int check) 
{
    int     price, 
            i, j, k,
            s, 
           *tmp_arr, 
           *null, 
           *value_arr, 
           *null_arr, 
            err;
    mixed   tmp;
    object *sold;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0, s = sizeof(ob); i < s; i++)
    {
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

	if (!shop_hook_allow_sell(ob[i]))
	    continue;

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
        change_money(null_arr + value_arr, TP);
	shop_hook_sell_get_money(text(value_arr));
    }

    return sold;
}

