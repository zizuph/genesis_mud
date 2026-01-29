inherit "/d/Genesis/ship/ship";
#include "local.h"
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
	PIER4,
	ROOM + "sea1",
	ROOM + "sea2",
	OPEN_SEA,
	ROOM + "sea4",
	ROOM + "sea5",
	/*... to and from Arcoron ...*/
	CITY3,
	CITY2,
	CITY1,
	CITYHARBOUR,
	CITY1,
	CITY2,
	CITY2,
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
	4,
	14,
	6,
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
    add_adj("passenger");
    set_long("This is a fairly large passenger ship. It can be used to transport " +
	     "goods as well, but usually it's so crowded with people that there " +
	     "is no room left to transport any goods. You see 16 oars sticking " +
	     "out on one side, and guess the number is the same on the other " +
	     "side. The wooden ship looks very well crafted. Some letters on the " +
	     "side of the ship indicates this ship runs between Palanthas and " +
	     "Arcoron.\n");
}

board(what)
{
    object ticket, *tmp;

    if (!board_enabled)
	return 0;
    if (what && (!sizeof(tmp =
                FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
               this_object() != tmp[0]))
	return 0;
    if (this_player()->query_average_stat() >= 20)
 	return ::board(what);

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}

