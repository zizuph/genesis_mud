#pragma save_binary

inherit "/std/monster";

#include <macros.h>
#include <money.h>
#include <cmdparse.h>

static	string 	ticket; 	/* If the captain sell tickets */
static	int	ticket_price;  	/* Price of ticket if we have one. */

/*
 * Function name: create_captain
 * Description:   The standard create routine
 */
void
create_captain() {}

/*
 * Function name: create_monster
 * Description:   The standard create rutine
 */
void
create_monster()
{
    create_captain();
}

nomask void
reset_monster() { this_object()->reset_captain(); }

/*
 * Function name: init_living
 * Description:   The normal init_living
 */
void
init_living()
{
    ::init_living();
    
    if (ticket)
        add_action("buy", "buy");
}

/*
 * Function name: set_ticket
 * Description:   Set the filename of the ticket
 * Arguments:     file - Ticket file
 */
public void
set_ticket(string file)
{
    ticket = file;
}

/*
 * Function name: query_ticket
 * Description:   Query the ticket file
 */
public string
query_ticket()
{
    return ticket;
}

/*
 * Function name: set_price
 * Description:   Set the price of the ticket
 */
public void
set_price(int i)
{
    ticket_price = i;
}

/*
 * Function name: query_price
 * Description:   What's the price
 */
public int
query_price()
{
    return ticket_price;
}

/*
 * Function name: buy
 * Description:   Try to buy a ticket
 */
int
buy(string str)
{
    object buy_ob, *tmp;
    string what, from;
    int    *result, m_res, price;

    if (!str)
    {
	notify_fail("Buy what?\n");
	return 0;
    }

    if (sscanf(str, "%s from %s", what, from) != 2)
    {
	what = str;
	from = "";
    }

    if (what != "ticket")
    {
	notify_fail("I have no such thing for sale.\n");
	return 0;
    }

    if (strlen(from) &&
	(!sizeof(tmp = FIND_STR_IN_OBJECT(from, environment(this_player()))) ||
	 this_object() != tmp[0]))
    {
	notify_fail("Buy ticket from whom?\n");
	return 0;
    }

    if (this_player()->query_prop("_live_i_killed_captain")) {
	notify_fail("I refuse to sell tickets to people killing my brethren!\n");
	return 0;
    }

    buy_ob = clone_object(ticket);
    if (!buy_ob) {
	notify_fail("I seem to be out of tickets.\n");
	return 0;
    }

    if (!MONEY_ADD(this_player(), -ticket_price))
    {
	buy_ob->remove_object();
	write("You cannot afford the ticket.\n");
	return 1;
    }

    if (buy_ob->move(this_player()))
    {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
	    " on the ground.\n");
	buy_ob->move(environment(this_player()));
    }
    else
    {
	write("You get your " + buy_ob->short() + ".\n");
	say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }
    return 1;
}

/*
 * Function name: second_life
 * Description:   Handles things that are particular to a dying captain
 * Arguments:     Object that caused the death
 * Returns:       False
 */
public int
second_life(object killer)
{
    if (killer && living(killer))
	killer->add_prop("_live_i_killed_captain", 1);
}
