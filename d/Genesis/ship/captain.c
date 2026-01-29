#pragma save_binary

inherit "/std/monster";

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>

static	string 	ticket; 	/* If the captain sell tickets */
static	int	ticket_price;  	/* Price of ticket if we have one. */
static  int     newbie_stats;   /* Stats below which a player rides for free */

#define LIVE_I_KILLED_CAPTAIN "_live_i_killed_captain"

/*
 * Function name: create_captain
 * Description:   The standard create routine
 */
void
create_captain()
{
}

/*
 * Function name: create_monster
 * Description:   The standard create rutine
 */
void
create_monster()
{
    ticket_price = 30; /* cc */
    newbie_stats = 15;

    create_captain();
}

void
reset_monster()
{
    this_object()->reset_captain();
}

/* 
 * Function name: query_ride_for_free
 * Description:   May a player board without a ticket?
 * Arguments:     object player
 * Returns:       int 1 if allowed to board
 */
public int
query_ride_for_free(object player)
{
    return (player->query_average_stat() < newbie_stats);
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
 * Function name: set_newbie_stats
 * Description	: Set the stat level below which players ride for free
 */
public void
set_newbie_stats(int stats)
{
    newbie_stats = stats;
}

/*
 * Function name: query_newbie_stats
 * Description	: Returns the stat level below which players ride for free
 */
public int
query_newbie_stats()
{
    return newbie_stats;
}

/*
 * Function name: buy
 * Description:   Try to buy a ticket
 */
int
buy(string str)
{
    object obj, steed, *tmp, *targets;
    string what, from = "", for_whom = "";
    int    index, size;

    if (!str || !query_ticket())
    {
	notify_fail("Buy what [for whom] [from whom]?\n");
	return 0;
    }

    /* Admittedly a rather ugly way to test for three syntaxes. */
    if (sscanf(str, "%s for %s from %s", what, for_whom, from) != 3)
    {
        if (sscanf(str, "%s for %s", what, for_whom) != 2)
        {
            if (sscanf(str, "%s from %s", what, from) != 2)
            {
                what = str;
            }
        }
    }

    if ((what != "ticket") && (what != "tickets"))
    {
	notify_fail("I have no such thing for sale.\n");
	return 0;
    }

    if (strlen(from) &&
	(!sizeof(tmp = FIND_STR_IN_OBJECT(from, environment(this_player()))) ||
	 this_object() != tmp[0]))
    {
	notify_fail("Buy " + what + " from whom?\n");
	return 0;
    }

    if (this_player()->query_prop(LIVE_I_KILLED_CAPTAIN))
    {
	notify_fail("I refuse to sell tickets to people killing my brethren!\n");
	return 0;
    }

    if (strlen(for_whom))
    {
        targets = PARSE_THIS(for_whom, "[the] %l");
        if ((for_whom == "me") || (for_whom == "team") || (for_whom == "all"))
        {
            targets += ({ this_player() });
        }
        targets = FILTER_PLAYERS(targets);
        if (!sizeof(targets))
        {
	    notify_fail("Buy " + what + " for whom?\n");
	    return 0;
        }
    }
    else
    {
        targets = ({ this_player() });
    }

    if (sizeof(tmp = filter(targets, query_ride_for_free)))
    {
        if (member_array(this_player(), tmp) > -1)
        {
            write("You're so small and tiny that I'll let you ride for free. " +
                "You can board without a ticket.\n");
            tmp -= ({ this_player() });
            targets -= ({ this_player() });
        }
        if (size = sizeof(tmp))
        {
            write(FO_COMPOSITE_LIVE(tmp, this_player()) + " " +
                ((size == 1) ? "is" : "are") +
                " so small and tiny no ticket is required for " +
                ((size == 1) ? tmp[0]->query_objective() : "them") +
                " to board.\n");
        }
        targets -= tmp;
    }
    /* All too small to require a ticket. */
    if (!(size = sizeof(targets)))
    {
        return 1;
    }

    if (!MONEY_ADD(this_player(), (-ticket_price * size)))
    {
	write("You cannot afford " +
	    ((size == 1) ? "the ticket" : (LANG_NUM2WORD(size) + " tickets")) + ".\n");
	return 1;
    }

    /* Don't give the write message only for yourself. */
    if ((size > 1) || (targets[0] != this_player()))
    {
        write("You buy a ticket for " + FO_COMPOSITE_LIVE(targets, this_player()) + ".\n");
    }

    /* Loop over the players to buy tickets for. */
    for (index = 0; index < size; index++)
    {
        /* Refund if we cannot clone the ticket. Shouldn't happen. */
        if (!objectp(obj = clone_object(ticket)))
        {
            write(query_The_name(this_player()) +
                " seems to be out of tickets. You get your money refunded.\n");
            MONEY_ADD(this_player(), ticket_price);
            continue;
        }

        /* See if the player can carry the ticket. */
        if (obj->move(targets[index]))
        {
	    tell_object(targets[index], "You drop the " + obj->short() +
	        " on the ground.\n");
	    tell_room(environment(), QCTNAME(this_player()) + " drops " +
	        LANG_ASHORT(obj) + " on the ground.\n", targets[index]);
	    obj->move(environment(), 1);
        }
        else
        {
	    tell_object(targets[index], "You get " + LANG_ASHORT(obj) +
	        " from " + query_the_name(targets[index]) + ".\n");
        }
    }

    /* Loop over the players to buy tickets for their steeds, too. */
    tmp = ({ });
    for (index = 0; index < size; index++)
    {
        steed = targets[index]->query_prop(LIVE_O_STEED);
        /* If there is a steed, only pay once for the steed. */
        if (!objectp(steed) ||
            (member_array(steed, tmp) > -1))
        {
            continue;
        }
        /* Separate purchase for the steed. */
        if (!MONEY_ADD(this_player(), -ticket_price))
        {
            write("You cannot afford a ticket for " +
                steed->query_the_name(this_player()) + ".\n");
            continue;
        }

        /* Refund if we cannot clone the ticket. Shouldn't happen. */
        if (!objectp(obj = clone_object(ticket)))
        {
            write(query_The_name(this_player()) +
                " seems to be out of tickets. You get your money refunded.\n");
            MONEY_ADD(this_player(), ticket_price);
            continue;
        }

        /* See if the player can carry the ticket. */
        /* There could be a small caveat here if there are two or more on the
         * same steed, and the ticket is moved into a player who is not the
         * driver. However, I didn't fancy thinking about that eventuality too
         * much.
         */
        if (obj->move(targets[index]))
        {
	    tell_object(targets[index], "You drop " + LANG_THESHORT(obj) +
	        " for your " + steed->query_nonmet_name() + " on the ground.\n");
	    tell_room(environment(), QCTNAME(this_player()) + " drops " +
	        LANG_ASHORT(obj) + " on the ground.\n", targets[index]);
	    obj->move(environment(), 1);
        }
        else
        {
	    tell_object(targets[index], "You get " + LANG_ASHORT(obj) +
	        " from " + query_the_name(targets[index]) + " for your " +
	        steed->query_nonmet_name() + ".\n");
        }
        tmp += ({ steed });
    }
    if (sizeof(tmp))
    {
        write("You buy a ticket for " + FO_COMPOSITE_LIVE(tmp, this_player()) +
            " as well.\n");
    }
    /* Give message to onlookers in one go. */
    size += sizeof(tmp);
    say(QCTNAME(this_player()) + " buys " +
        ((size == 1) ? "a ticket" : (LANG_NUM2WORD(size) + " tickets")) + ".\n");

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
    
    if (ticket)
    {
        add_action(buy, "buy");
    }
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
    {
	killer->add_prop(LIVE_I_KILLED_CAPTAIN, 1);
    }
}
