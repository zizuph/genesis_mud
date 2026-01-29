#include <macros.h>
#include <language.h>
/*
 * This file should be included after the
 *      #inherit "/d/Genesis/ship/ship"
 * in order to allow horses to board the ship.
 * Of course, this will cost two tickets!
 *
 * Function name: board
 * Description	: Allow a player to board the ship if he have got a ticket, or
 *		  if the fare is free of charge
 *                The player can also take a horse along
 * Arguments	: str - what we want to enter
 * Returns	: 1 - success
 *		  0 - wrong parameters
 */
public int
board(string str)
{
    object *tickets, *tmp;
    object ob1, ob2;
    int i, ntickets = 1;

    if (!board_enabled || !strlen(str))
	return 0;
    if (!parse_command(str, environment(this_player()),
		      "%o 'with' %o", ob1, ob2))
    {
	ob2 = 0;
	if (!parse_command(str, environment(this_player()),
			   "%o", ob1))
	    return 0;
    }
    if (ob1 != this_object()) return 0;

    tickets = ({});
    if (query_ticket_id())
    {
        tmp = all_inventory(this_player());
        for (i=0; i<sizeof(tmp); i++)
	{
	    if (member_array(query_ticket_id(), tmp[i]->query_names()) >= 0)
	        tickets += ({ tmp[i] });
	}
    }

    if (ob2 && (!living(ob2) || ob2->query_race_name() != "horse"))
	return 0;

    if (ob2)
    {
	ntickets++;                          /* Add a ticket for horse */
	tmp = all_inventory(ob2->query_room());
	for (i=0; i<sizeof(tmp); i++)
	    if (living(tmp[i])) ntickets++;  /* Add tickets for riders */
    }

    environment(this_player())->set_dircmd(str);
		      /* This will allow team members to do exactly the
		       * same command their leader did.*/

    if (query_ticket_id() && sizeof(tickets) < ntickets )
    {
	if (query_captain())
 	{
	    tell_room(environment(),
		      QCTNAME(query_captain()) + " scowls menacingly "+
		      "at " + QTNAME(this_player()) + " and blocks " +
		      this_player()->query_possessive() + " way.\n",
		      this_player());
	    write(capitalize(query_captain()->query_the_name(this_player())) +
		" scowls at you.\n");
	    if (ntickets == 1) 
	    {
	        query_captain()->command("say You have no ticket, "+
				     this_player()->query_nonmet_name() + ".");
	    }
	    else
	    {
	        query_captain()->command("say You haven't enough tickets, "+
			   this_player()->query_nonmet_name() + ".");
		if (sizeof(tickets))
		{
	            query_captain()->command("say You need to buy "+
			   LANG_WNUM(ntickets - sizeof(tickets)) + " more.");
		}
		else
		{
	            query_captain()->command("say You need to buy "+
			   LANG_WNUM(ntickets - sizeof(tickets)) + " tickets.");
		}
	    }
	}
	else
	{
	    write("A ship officer prevents you from boarding the "+
		  short() + ".\n");
	    tell_room(environment(), QCNAME(this_player()) + " tries to "+
		      "board the " + short() + ", but is prevented.\n",
		      this_player());
	}
	return 1;
    }

    if (!query_ticket_id())
    {
	if (ob2)
	{
	    tell_room(environment(), QCTNAME(this_player()) + " and " +
		      this_player()->query_possessive() + " " +
		      ob2->short() + " boards the "+
		      short() + ".\n", this_player());
	    write("You and your " + ob2->short() + " board the " +
		      short() + ".\n");
	}
	else
	{
	    tell_room(environment(), QCTNAME(this_player()) + " boards the "+
		  short() + ".\n", this_player());
	    write("You board the " + short() + ".\n");
	}
    }
    else
    {
	for (i=0; i<ntickets; i++)
	    tickets[i]->remove_object();

	if (query_captain())
	{
	    if (ob2)
	    {
	        tell_room(environment(), QCNAME(this_player()) + " gives "+
		      this_player()->query_possessive() + " tickets to "+
		      QTNAME(query_captain()) + " and boards the " + short()+
		      ".\n", this_player());
		tell_room(environment(),
			  capitalize(this_player()->query_possessive()) + 
			  " " + ob2->short() + " is also led onboard.\n",
			  this_player());
	        write("You give your tickets to "+
		  query_captain()->query_the_name(this_player()) + " and "+
		  "board the " + short() + ".\n");
		write("Your " + ob2->short() + " is also led onboard.\n");
	    }
	    else
	    {
	        tell_room(environment(), QCNAME(this_player()) + " gives "+
		      this_player()->query_possessive() + " ticket to "+
		      QTNAME(query_captain()) + " and boards the " + short()+
		      ".\n", this_player());
	        write("You give your ticket to "+
		  query_captain()->query_the_name(this_player()) + " and "+
		  "board the " + short() + ".\n");
	    }
	}
    }

    this_player()->move_living("boarding the ship", query_deck()[0]);
    if (ob2) ob2->move_living("boarding the ship", query_deck()[0]);
    return 1;
}
