/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/lib/trade";

#include <ss_types.h>
#include <money.h>

#define	NUM	 sizeof(MONEY_TYPES)
#define STAT_LIM 20

/*
 * Global variables
 */

object ship;
string ticket_file;
string ship_info;

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    if (query_hp() > 0) return;
    if (ship)
	ship->stop_ship("The ship stops; someone killed the captain!\n");
    ::do_die(killer);
}

/*
 * Function name: set_ship
 * Description:   Set the ship object
 * Arguments:     s - the ship object
 */
public void
set_ship(object s)
{
    ship = s;
}

/*
 * Function name: set_ticket_file
 * Description:   Set the ticket file path name
 */
public void
set_ticket_file(string s)
{
    ticket_file = s;
}

/*
 * Function name: set_ship_info
 * Description:   Set the ship info string for the ask add_action
 */
public void
set_ship_info(string s)
{
    ship_info = s;
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    
    set_stats(({120, 180, 120, 180, 150, 190}));
    set_skill(SS_SWIM,      100);
    set_skill(SS_AWARENESS, 100);
    SET_MAX_HP;

    config_default_trade();
    enable_intro();
}

/*
 * Function name: init_living
 * Description:   A patch for the automatic attack if this mobile can do that
 */
public void
init_living()
{
    ::init_living();
    add_action("buy", "buy");
    add_action("ask", "ask");
}

/*
 * Function name: buy
 * Description:   Try to buy a ticket
 */
public int
buy(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;
    int    *result, m_res, price;

    if (!str) {
	NF("Buy what?\n");
	return 0;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;
    if (what != "ticket") {
	NF("I have no such thing for sale.\n");
	return 0;
    }
    buy_ob = clone_object(ticket_file);
    if (!buy_ob) {
	NF("I seem to be out of tickets.\n");
	return 0;
    }
    if (TP->query_average_stat() <= STAT_LIM) {
	buy_ob -> add_prop(OBJ_I_VALUE, 0);
    } else {
        price = buy_ob->query_prop(OBJ_I_VALUE);
        result = pay(price, this_player(), for_c, 0, 0, get_c);
        if (sizeof(result) == 1) {
            buy_ob->remove_object();
            return 0;
        }
        write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
        if (change)
	    write("You get " + change + " as change.\n");
    }

    if (buy_ob->move(TP)) {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(TP) + " drops one " + buy_ob->short() +
	    " on the ground.\n");
	buy_ob->move(ETP);
    } else {
	write("You get your " + buy_ob->short() + ".\n");
	say(QCTNAME(TP) + " buys a " + buy_ob->short() + ".\n");
    }
    return 1;
}

/*
 * Function name: ask
 * Description:   Handle the ask action
 * Returns:       1/0
 */
public int
ask(string str)
{
    object who;
    string what;

    NF("Ask who about what?\n");
    if (!strlen(str)) 
	return 0;

    if (!parse_command(str, environment(), " %o 'about' / 'for' %s ",
		       who, what))
	return 0;

    if (!who)
	return 0;
    
    if (who != TO)
	return 0;
    
    if (!what)
	return 0;
    
    if (what == "ship" || what == "your ship" || what == "boat" ||
	what == "your boat" || what == "sailing ship" ||
	what == "destination") {
	command("say " + ship_info);
	return 1;
    }
    
    if (what == "ticket" || what == "cost") {
	command("say A ticket costs normally 30 copper coins.");
	command("say You can buy them from me.");
	command("smile");
	return 1;
    }
    
    command("shrug");
    command("say Sorry, but I don't understand your question.");
    return 1;
}


