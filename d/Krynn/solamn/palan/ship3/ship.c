inherit "/d/Genesis/ship/ship";
#include "/d/Krynn/solamn/palan/ship3/local.h"
#include <cmdparse.h>

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(CABIN);
    add_cabin(CABIN2);
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_places_to_go(({
	PIER3,
	ROOM + "sea1",
	ROOM + "sea2",
	OPEN_SEA,
	ROOM + "sea4",
	ROOM + "sea5",
	/*... to and from Newports ...*/
	NEWP1,
	NEWP2,
	NEWPORTS,
	NEWP2,
	NEWP1,
	/* */
	ROOM + "sea5",
	ROOM + "sea4",
	OPEN_SEA,
	ROOM + "sea2",
	ROOM + "sea1",
    }));

    set_time_between_stops(({
	16,
	3,
        5,
        2,
	2,
	3,
        /*to and from newports */
	3,
	1,
	14,
	3,
	1,
	/* */
	3,
        2,
        4,
        2,
	5
    }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("coastshipping");
    add_adj("merchant");
    set_long(break_string("This is a not so large coastshipping merchantman. " +
        "You see 4 oars sticking out on one side, and guess the number is " +
        "the same on the other side. The wooden ship looks very well " +
	"crafted. Some letters on the side of the ship indicates this " +
	"ship runs between Palanthas and Newports. " +
        "\n", 70));
}

board(what)
{
    object ticket, *tmp, armymaster, captain;
    string my_army, army_holding;

    captain = find_object("/d/Krynn/solamn/palan/ship3/captain");
    armymaster = find_object("/d/Krynn/common/warfare/armymaster");

    my_army = armymaster->army_of_player(this_player());

    army_holding = armymaster->army_in_area("Newports Area");

    if (!board_enabled)
	return 0;
    if (what && (!sizeof(tmp =
                FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
               this_object() != tmp[0]))
	return 0;
    if ( (find_object(NEWPORTS) == environment(this_player())) &&
	 (environment(captain) == environment(this_player())) )
    {
	if ((my_army != army_holding) && (army_holding != "Free People"))
	{
	    if (my_army == "Knights")
	    {
		captain->command("say Solamnian Knights are not allowed "+
				 "to board by orders from the "+
				 army_holding + ".\n");
		return 1;
	    }
	    else if(army_holding == "Knights")
	    {
		if(my_army != "Free People")
		{
		    captain->command("say Dragonarmy Members are not allowed "+
				     "to board by orders from the "+
				     army_holding + ".\n");
		    return 1;
		}
	    }
	}
    }

    if (this_player()->query_average_stat() >= 20)
 	return ::board(what);

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}

