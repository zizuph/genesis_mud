// /d/Avenir/inherit/shop.c
/*
 *  Features that differ from /d/Genesis/lib/shop:
 *  - Shopkeeper
 *  - Check for special items that are not bought
 *  - greed is set using VBFC discriminate()
 *
 *  Olorin, July 1994
 *
 *  Modification log: Adopted and Modified as standard Avenir shop
 *                         by Ilyian, May 1995 (by permission from Olorin
 *                         and Elessar.
 *                         Made reset call arm_me in the shopkeeper.
 *                         any armed shopkeeper should have an arm_me 
 *                         defined as arming routine. Glinda may-95.
 *
 * Enriched version:
 *   * No longer acts as a room - now it's more useful.
 *   * Made the shopkeeper more useful.
 *
 */
//inherit "/d/Genesis/lib/shop";
inherit "/d/Avenir/inherit/shop_list";

#include <macros.h>
#include <language.h>
#include <ss_types.h>


public int discriminate(void);


/*
 * Global variables
 */
public static object keeper;
public static int no_armours, no_weapons;
public static string keeper_file, *no_sell_prop = ({}), *enemies = ({});
public static string *hated_race, *suspected_race, *favoured_race;


public void
set_keeper_file(string str)		{ keeper_file = str; }

public void
set_hated_race(string *races)		{ hated_race = races; }

public void
set_suspected_race(string *races)	{ suspected_race = races; }

public void
set_favoured_race(string *races)	{ favoured_race = races; }

public void
set_no_buy_armours(int i)		{ no_armours = i; }

public void
set_no_buy_weapons(int i)		{ no_weapons = i; }

public void
set_no_sell_prop(mixed str)
{
    if (stringp(str))
	no_sell_prop = ({ str });
    else if (pointerp(str))
	no_sell_prop = str;
}

public void
config_shop(void)
{
    config_default_trade();

    set_money_give_max(1000);
    set_money_give_out(   ({ 10000,   700,  40,    1 }));
    set_money_give_reduce(({     0,     4,   3,    9 }));

    set_money_greed_sell(discriminate);
    set_money_greed_buy(discriminate);
    set_money_greed_change(discriminate);
}

public void
fix_keeper(void)
{
    if (objectp(keeper))
    {
	keeper->move(this_object());
    }
    else if (strlen(keeper_file))
    {
	keeper = clone_object(keeper_file);
	keeper->arm_me();
	keeper->move(this_object());
    }
}

public int
check_keeper(void)
{
    if (keeper && present(keeper, this_object()))
    {
	object enemy = keeper->query_attack();

	if (objectp(enemy))
	{
	    if (enemy == this_player())
	    {
		notify_fail("The shopkeeper is trying to kill you, "+
		    "so you cannot do that!\n");
	    }
	    else
	    {
		notify_fail("The shopkeeper is busy fighting, "+
		    "so you cannot do that!\n");
	    }

	    return 0;
	}

	return 1;
    }
    else
    {
	notify_fail("There is no shopkeeper here, so you cannot do that!\n");
	return 0;
    }
}

public int
keeper_speak(string msg)
{
    if (keeper && present(keeper, this_object()))
    {
	notify_fail("");
	return keeper->command("say "+ msg);
    }

    return 0;
}

public int
do_buy(string args)
{
    if (check_keeper())
	return ::do_buy(args);

    return 0;
}

public int
do_value(string args)
{
    if (check_keeper())
	return ::do_value(args);

    return 0;
}

public int
do_sell(string args)
{
    if (check_keeper())
	return ::do_sell(args);

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
    if (keeper_speak("You don't have any " + str + "."))
	return 1;

    return ::shop_hook_sell_no_match(str);
}

public int
shop_hook_sold_nothing(void)
{
    if (keeper_speak("You didn't have much to sell."))
	return 1;

    return ::shop_hook_sold_nothing();
}

public void
shop_hook_sell_no_value(object ob)
{
    if (keeper_speak("The "+ ob->short() +" is worthless to me."))
	return;

    ::shop_hook_sell_no_value(ob);
}

public void
shop_hook_sell_no_sell(object ob, string str)
{
    if (!strlen(str) && keeper_speak("I don't buy such items."))
	return;

    ::shop_hook_sell_no_sell(ob, str);
}

public void
shop_hook_sell_object_stuck(object ob, int err)
{
    if (keeper_speak("It seems you are stuck with that."))
	return;

    ::shop_hook_sell_object_stuck(ob, err);
}

public void
shop_hook_sell_get_money(string str)
{
    if (keeper && present(keeper, this_object()))
    {
	write(keeper->query_The_name(this_player()) +
	    " gives you " + str + ".\n");
	return;
    }

    ::shop_hook_sell_get_money(str);
}

public void
shop_hook_buy_no_match(string str)
{
    if (keeper_speak("I have no " + str + " to sell."))
	return;

    ::shop_hook_buy_no_match(str);
}

public void
shop_hook_buy_cant_carry(object ob, int err)
{
    if (keeper_speak("You can't carry more, I'm afraid."))
    {
	say(QCTNAME(keeper) +" drops the "+ ob->short() +
	    "onto the floor.\n");
	return;
    }

    ::shop_hook_buy_cant_carry(ob, err);
}

public void
shop_hook_buy_cant_pay(object ob, int *arr)
{
    if (keeper_speak("You can't seem to afford that."))
	return;

    ::shop_hook_buy_cant_pay(ob, arr);
}

public void
shop_hook_buy_magic_money(object ob)
{
    if (keeper_speak("You are carrying magic money, no deal!"))
	return;

    ::shop_hook_buy_magic_money(ob);
}

public void
shop_hook_buy_pay_money(string str, string change)
{
    if (keeper && present(keeper, this_object()))
    {
	write("You give "+ str +" to "+
	    keeper->query_the_name(this_player()) +".\n");

	if (change)
	{
	    write(capitalize(keeper->query_pronoun()) +
		" gives you " + change + " back.\n");
	}

	return;
    }

    ::shop_hook_buy_pay_money(str, change);
}

public void
shop_hook_value_not_interesting(object ob)
{
    if (keeper_speak("That item doesn't interest me."))
	return;

    ::shop_hook_value_not_interesting(ob);
}

public void
shop_hook_value_held(object ob, string text)
{
    if (keeper_speak("I could offer about " + text +
	    " for your " + ob->short() + "."))
    {
	return;
    }

    ::shop_hook_value_held(ob, text);
}

public void
shop_hook_value_store(object ob, string text)
{
    if (keeper_speak("I value the " + ob->short() + " to "+ text +"."))
	return;

    ::shop_hook_value_store(ob, text);
}

public void
shop_hook_value_asking(string str)
{
    if (keeper && present(keeper, this_object()))
    {
	say(QCTNAME(this_player())+" asks something of "+
	    QTNAME(keeper) +".\n");
	return;
    }

    ::shop_hook_value_asking(str);
}

public int
shop_hook_value_no_match(string str)
{
    if (keeper_speak("We hold no '" + str + "' in stock."))
	return 1;

    return ::shop_hook_value_no_match(str);
}

public void
shop_hook_list_empty_store(string str)
{
    if (keeper_speak("We are currently sold out."))
	return;

    ::shop_hook_list_empty_store(str);
}

public int
shop_hook_list_no_match(string str)
{
    if (keeper_speak("We have no '" + str + "' in stock."))
	return 1;

    return ::shop_hook_list_no_match(str);
}

/* Custom hook. */
public void
shop_hook_stolen_item(object what)
{
    if (keeper_speak("Where did you get this " + what->short() + "?"))
    {
	keeper->command("say You must have stolen it ... or worse!");
	keeper->command("say Your business is no longer welcome here.");
	return;
    }

    notify_fail("This shop does not traffic in stolen items.\n");
}

/* Custom hook. */
public void
shop_hook_no_business()
{
    if (keeper_speak("I do not want your business, " +
	    (this_player()->query_gender() ? "Lady" : "Mister") + "!"))
    {
	return;
    }

    notify_fail("Your business is not welcome here.\n");
}

/* Custom hook. */
public void
shop_hook_no_weapons(object ob)
{
    if (keeper_speak("I am not interested in your weapons."))
	return;

    notify_fail("This shop does not buy weapons.\n");
}

/* Custom hook. */
public void
shop_hook_no_armours(object ob)
{
    if (keeper_speak("I am not interested in your armours."))
	return;

    notify_fail("This shop does not buy armours.\n");
}

/*
 * Function name: shop_hook_allow_sell
 * Description:   If you want to do more testing on objects
 *                the player intend to sell.
 * Argument:      ob - The object player wants to sell
 * Returns:       1 if we allow player to sell the object (default)
 */
public int
shop_hook_allow_sell(object ob)
{
    int     i;
    mixed   prop = 0;
    string  name = this_player()->query_real_name();

    if (IN_ARRAY(name, enemies))
    {
	shop_hook_no_business();
	return 0;
    }

    for (i = 0; i < sizeof(no_sell_prop); i++)
    {
	if (prop = ob->query_prop(no_sell_prop[i]))
	{
	    if (stringp(prop))
		notify_fail(prop);
	    else
		shop_hook_stolen_item(ob);

	    enemies += ({ name });
	    return 0;
	}
    }

    if (no_armours && armour_filter(({ ob })))
    {
	shop_hook_no_armours(ob);
	return 0;
    }

    if (no_weapons && weapon_filter(({ ob })))
    {
	shop_hook_no_weapons(ob);
	return 0;
    }

    return 1;
}

/*
 * Function name: shop_hook_allow_buy
 * Description:   A hook to use if you want to test the object
 *                further if you allow it to be bought
 * Arguments:     ob - The object player wants to buy.
 * Returns:       1 if we allow it to be bought (default)
 */
public int
shop_hook_allow_buy(object ob)
{
    if (IN_ARRAY(this_player()->query_real_name(), enemies))
    {
	shop_hook_no_business();
	return 0;
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
discriminate(void)
{
    string race = this_player()->query_race_name();
    int bargain = this_player()->query_skill(SS_TRADING);

    if (bargain > 30)
	bargain = 30;

    bargain = 115 - bargain;

    if (IN_ARRAY(race, hated_race))
	bargain = (bargain * 120) / 100;
    else if (IN_ARRAY(race, suspected_race))
	bargain = (bargain * 110) / 100;
    else if (IN_ARRAY(race, favoured_race))
	bargain = (bargain * 90) / 100;

    return bargain;
}
