#pragma save_binary

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>

#include "../ships.h"

inherit "/std/monster";

static	string ticket; 	/* If the captain sell tickets */
static  string dest;    /* What is our next port */
static  int    ship_id; /* Ship Id to which the captain is bound to */
static  int    announce_alarm; /* alarm to announce departures */
static  float  extra_time; /* extra time beyond current alarm */

#define LIVE_I_KILLED_CAPTAIN "_live_i_killed_captain"

void   create_captain      ();
varargs
void   set_ship_id         (int id);
string query_ticket        ();
int    buy                 (string str);
int    is_captain          ();
string describe_route      ();
string describe_ticket     ();
int    query_ride_for_free (object candidate);
void   announce_loading    (string next_port);
void   announce_last_call  (string next_port);
void   announce_departure  (string next_port);

public string
captain_default_answer()
{
    command("say I can only talk about routes and tickets.\n");
    return "";
}

/*
 * Function name: create_captain
 * Description:   The standard create routine
 */
void
create_captain ()
{
  if (!IS_CLONE)
    return;
  
  ship_id = SHIP_MANAGER->find_ship_by_captain(MASTER_OB(TO));
	if(ship_id != -1)
		ticket = query_ticket();

	add_prop(
		OBJ_M_NO_ATTACK,
		"Genesis ShipLines personnel cannot be attacked.\n"
	);
	add_prop(
		OBJ_M_NO_MAGIC_ATTACK,
		"Genesis ShipLines personnel cannot be attacked.\n"
	);
	add_prop(
 	  LIVE_M_NO_ACCEPT_GIVE,
		"Genesis ShipLines personnel do not accept gifts.\n"
	);
	set_default_answer(captain_default_answer);
	add_ask(
		({"route", "destination"}),
		describe_route
	);
	add_ask(
		({"ticket", "price"}),
		describe_ticket
	);
	add_name("captain");
}

/*
 * Function name: create_monster
 * Description:   The standard create rutine
 */
void
create_monster ()
{
	::create_monster;
	create_captain();
}

varargs void
set_ship_id (int id = -1)
{
  if (id != -1) {
    ship_id = id;
    return;
  }
	ship_id = SHIP_MANAGER->find_ship_by_captain(file_name(TO));
}

int
query_ship_id ()
{
  return ship_id;
}

void
reset_monster ()
{
	this_object->reset_captain();
}

string
query_ticket ()
{
	return SHIP_MANAGER->get_ticket_for_ship(ship_id);
}

/*
 * Function name: buy
 * Description:   Try to buy a ticket
 */

int
buy(string str)
{
	object ticket_obj, steed, *tmp, *targets;
	string what, from = "", for_whom = "";
	int    index, size, ticket_price;

	if (!str || !ticket)
		NF0("Buy what [for whom] [from whom]?\n");

    /* Admittedly a rather ugly way to test for three syntaxes. */
	if (sscanf(str, "%s for %s from %s", what, for_whom, from) != 3)
		if (sscanf(str, "%s for %s", what, for_whom) != 2)
			if (sscanf(str, "%s from %s", what, from) != 2)
				what = str;
	if ((what != "ticket") && (what != "tickets"))
		NF0("I have no such thing for sale.\n");
	if (
		strlen(from) &&
		(!sizeof(tmp = FIND_STR_IN_OBJECT(from, environment(TP))) ||
		this_object() != tmp[0])
	)
		NF0("Buy " + what + " from whom?\n");
	if (TP->query_prop(LIVE_I_KILLED_CAPTAIN))
		NF0("I refuse to sell tickets to people killing my brethren!\n");
	if (strlen(for_whom)) {
		targets = PARSE_THIS(for_whom, "[the] %l");
		if ((for_whom == "me") || (for_whom == "team") || (for_whom == "all"))
			targets += ({ TP });
		targets = FILTER_PLAYERS(targets);
		if (!sizeof(targets))
	    NF0("Buy " + what + " for whom?\n");
	}
	else
		targets = ({ TP });
	if (sizeof(tmp = filter(targets, query_ride_for_free))) {
		if (IN_ARRAY(TP, tmp)) {
			write("You're so small and tiny that I'll let you ride for free. " +
						"You can board without a ticket.\n");
			tmp -= ({ TP });
			targets -= ({ TP });
		}
		if (size = sizeof(tmp))	{
			write(
				FO_COMPOSITE_LIVE(tmp, TP) + " " +
				((size == 1) ? "is" : "are") +
				" so small and tiny no ticket is required for " +
				((size == 1) ? tmp[0]->query_objective() : "them") +
				" to board.\n"
			);
		}
		targets -= tmp;
	}
	/* All too small to require a ticket. */
	if (!(size = sizeof(targets)))
		return 1;

	ticket_price = ticket->query_price();
	if (!MONEY_ADD(TP, (-ticket_price * size))) {
		write(
			"You cannot afford " +
	    ((size == 1) ? "the ticket" : (LANG_NUM2WORD(size) + " tickets")) +
			".\n"
		);
		return 1;
	}

	/* Don't give the write message only for yourself. */
	if ((size > 1) || (targets[0] != TP))
		write("You buy a ticket for " + FO_COMPOSITE_LIVE(targets, TP) + ".\n");

    /* Loop over the players to buy tickets for. */
	for (index = 0; index < size; index++) {
        /* Refund if we cannot clone the ticket. Shouldn't happen. */
		if (!objectp(ticket_obj = clone_object(ticket))) {
			write(
				query_The_name(TO) +
				" seems to be out of tickets. You get your money refunded.\n"
			);
			MONEY_ADD(TP, ticket_price);
			continue;
		}

		/* See if the player can carry the ticket. */
		if (ticket_obj->move(targets[index])) {
	    tell_object(
				targets[index], "You drop the " + ticket_obj->short() +
				" on the ground.\n"
			);
	    tell_room(
				environment(), QCTNAME(TP) + " drops " +
	      LANG_ASHORT(ticket_obj) + " on the ground.\n", targets[index]
			);
	    ticket_obj->move(environment(), 1);
		}
		else
	    tell_object(
				targets[index],
				"You get " + LANG_ASHORT(ticket_obj) +
				" from " + query_the_name(targets[index]) + ".\n"
			);
	}

	/* Loop over the players to buy tickets for their steeds, too. */
	tmp = ({ });
	for (index = 0; index < size; index++) {
		steed = targets[index]->query_prop(LIVE_O_STEED);
		/* If there is a steed, only pay once for the steed. */
		if (!objectp(steed) || IN_ARRAY(steed, tmp))
			continue;

		/* Separate purchase for the steed. */
		if (!MONEY_ADD(TP, -ticket_price)) {
			write(
				"You cannot afford a ticket for " +
				steed->query_the_name(TP) + ".\n"
			);
			continue;
		}

		/* Refund if we cannot clone the ticket. Shouldn't happen. */
		if (!objectp(ticket_obj = clone_object(ticket))) {
			write(
				query_The_name(TO) +
				" seems to be out of tickets. You get your money refunded.\n"
			);
			MONEY_ADD(TP, ticket_price);
			continue;
		}

		/* See if the player can carry the ticket. */
		/* There could be a small caveat here if there are two or more on the
		 * same steed, and the ticket is moved into a player who is not the
		 * driver. However, I didn't fancy thinking about that eventuality too
		 * much.
		 */
		if (ticket_obj->move(targets[index])) {
	    tell_object(
				targets[index], "You drop " + LANG_THESHORT(ticket_obj) +
				" for your " + steed->query_nonmet_name() + " on the ground.\n"
			);
	    tell_room(
				environment(), QCTNAME(TP) + " drops " +
				LANG_ASHORT(ticket_obj) + " on the ground.\n", targets[index]
			);
	    ticket_obj->move(environment(), 1);
		}
		else
	    tell_object(
				targets[index],
				"You get " + LANG_ASHORT(ticket_obj) +
	      " from " + query_the_name(targets[index]) + " for your " +
	      steed->query_nonmet_name() + ".\n"
			);
		tmp += ({ steed });
	}
	if (sizeof(tmp)) {
		write(
			"You buy a ticket for " + FO_COMPOSITE_LIVE(tmp, TP) +
			" as well.\n"
		);
	}
    /* Give message to onlookers in one go. */
	size += sizeof(tmp);
	say(
		QCTNAME(TP) + " buys " +
		((size == 1) ? "a ticket" : (LANG_NUM2WORD(size) + " tickets")) + ".\n"
	);

	return 1;
}

/*
 * Function name: init_living
 * Description:   The normal init_living
 */
void
init_living()
{
	::init_living();
    
	if(ticket)
		add_action(buy, "buy");
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
		killer->add_prop(LIVE_I_KILLED_CAPTAIN, 1);
}

public nomask int
is_captain ()
{
  return 1;
}

/* Should be called by the master */

void
init_captain ()
{
	set_ship_id();
	if(ship_id != -1)
		ticket = query_ticket();
}
	
string
describe_route ()
{
	string reply;
	
	if(ship_id == -1) {
		command("say sorry, I am currently unassigned\n");
		return "";
	}
	reply = SHIP_MANAGER->construct_captain_route_reply(ship_id);
	command("say " + reply);
	return "";
}

void
set_destination (string destination)
{
  dest = destination;
}

string
query_destination ()
{
  return dest;
}

string
describe_ticket ()
{

	if(ship_id == -1) {
		command("say sorry, I am currently not captaining a ship\n");
		return "";
	}
	if(! ticket) {
		command("say there are no tickets for this ship\n");
		return "";
	}
	command(
		"say The ticket for this ship costs " + ticket->query_price() +
		" copper coins\n"
	);
	return "";
}

int
query_ride_for_free (object candidate)
{
	if(interactive(candidate) && candidate->query_average() <= FREE_RIDE_AVG)
		return 1;
	return 0;
}

void
announce_loading (string next_port)
{
    remove_alarm(announce_alarm);

	command(
		"say Welcome to Genesis ShipLines! The "+
		SHIP_MANAGER->get_ship_description(ship_id) + " " +
		"leaves for " + next_port + " in " + ftoi(STOP_TIME_AT_PORT) +
		" seconds!"
	);
	command(
		"say Buy your tickets or stay ashore!"
	);
	announce_alarm = set_alarm(
		STOP_TIME_AT_PORT - STOP_TIME_AT_PORT/3.0,
		0.0,
		&announce_last_call(next_port)
	);
  set_destination(next_port);
	extra_time = STOP_TIME_AT_PORT / 3.0;
}

void
announce_last_call (string next_port)
{
    remove_alarm(announce_alarm);

	command(
		"say Last Call from Genesis ShipLines! The "+
		SHIP_MANAGER->get_ship_description(ship_id) + " " +
		"leaves for " + next_port + " in " + ftoi(STOP_TIME_AT_PORT/3.0) +
		" seconds! Buy your tickets or stay ashore!"
	);
	announce_alarm = set_alarm(
		STOP_TIME_AT_PORT/3.0,
		0.0,
		&announce_departure(next_port)
	);
	extra_time = 0.0;
}

void
announce_departure (string next_port)
{
	object ship;

	command("say Let's go! See you at " + next_port + "!");
	ship = SHIP_MANAGER->get_ship_object(ship_id);
	move_living("boarding the ship", ship->query_deck()[0]);
	ship->signal_master("navigate");
}

/* 
 * Function:    disable_boarding
 * Description: When the ship is set to not allow boarding, we need to
 *              remove the announcement alarms.
 */
public void
disable_boarding()
{
    object ship;
    
    if (get_alarm(announce_alarm))
    {
        ship = SHIP_MANAGER->get_ship_object(ship_id);
        if (objectp(ship))
        {
            // This means that the captain is in the boarding process. We
            // move the captain back up to the ship as the boarding has
            // been disabled.
            command("say Looks like we're being grounded. I'll wait "
                + "onboard!");
            move_living("boarding the ship", ship->query_deck()[0]);
        }
        remove_alarm(announce_alarm);
        announce_alarm = 0;
        extra_time = 0;
    }
}

public int
query_active_loading()
{
    if (get_alarm(announce_alarm))
    {
        return 1;
    }
    
    return 0;
}

public float
query_time_until_departure()
{
    if (!query_active_loading())
    {
        return 0;
    }
    
    mixed * call = get_alarm(announce_alarm);
    return call[2] + extra_time;
}
