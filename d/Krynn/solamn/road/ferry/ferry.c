 
inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

int stop_next = 0;

void
create_ship()
{
    object cap;

    seteuid(getuid());
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);

    set_places_to_go(({ PIER_EAST,
			    RIVER1,
			    RIVER2,
			    RIVER3,
			    PIER_WEST,
			    RIVER3,
			    RIVER2,
			    RIVER1,
			    }));

    set_time_between_stops(({ 15,
				  7,
				  5,
				  7,
				  15,
				  7,
				  7,
				  5
				  }));

    set_ticket_id(TICKET_NAME);
    set_name("ferry");
    add_name(SHIP_NAME);
    add_adj("small");
    add_adj("creaking");
    set_long("This is a small creaking ferry used for transport across the " +
	     "Vingaard River during a flood.\n");
	    
}

int
board(string what)
{
    object ticket, *tmp;

    if (!board_enabled)
	return 0;
    if (what && (!sizeof(tmp =
                FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
               this_object() != tmp[0]))
	return 0;
    
    if (ARMYMASTER->query_occupant(AREA_NAME) != "Free People" &&
	ARMYMASTER->get_army(this_player()) != ARMYMASTER->query_occupant(AREA_NAME))
    {
	notify_fail("The ferryman says: You're not a member of the current " +
		    "authorities, you are not allowed to board.\n");
	return 0;
    }

    if (this_player()->query_average_stat() >= 20)
 	return ::board(what);

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}

void
stop_at_next_possibility()
{
    /* well, not exactly next possibility, but rather immediately ;-) */
    stop_ship("The ferry suddenly crashes hard on something solid due " +
	      "to the rapidly retreating water. You are thrown onto " +
	      "the ground next to the ferry.\n");
    all_inventory(query_deck())->move(places_to_go[location],1);
    query_captain()->go_home();
    set_alarm(0.1,0.0,remove_object);
}
