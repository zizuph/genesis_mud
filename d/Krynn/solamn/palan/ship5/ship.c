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
    add_deck(DECK2);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_places_to_go(({
	PIER1,
	ROOM + "sea1",
	ROOM + "sea2",
	OPEN_SEA,
	ROOM + "sea4",
	ROOM + "sea5",
	/*... to and from Grey Havens ...*/
	SHIRE1,
	SHIRE2,
	SHIRE3,
	SHIRE4,
	GREY_HAVENS,
	SHIRE4,
	SHIRE3,
	SHIRE2,
	SHIRE1,
	/* */
	ROOM + "sea5",
	ROOM + "sea4",
	OPEN_SEA,
	ROOM + "sea2",
	ROOM + "sea1",
    }));

    set_time_between_stops(({
	23,
	7,
        5,
        7,
	4,
	3,
        /*to and from grey havens */
	5,
	8,
	3,
	5,
	24,
	4,
	2,
	7,
	3,
	/* */
	3,
        7,
        4,
        7,
	5
    }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("rough");
    add_adj("merchant");
    set_long(break_string("This is a large ocean-going merchant ship. " +
        "You see 18 oars sticking out on one side, and guess the number is " +
        "the same on the other side. The wooden ship looks very well " +
	"crafted. Some letters on the side of the ship indicates this " +
	"ship runs between Palanthas and Grey Havens. " +
        "\n", 70));
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

