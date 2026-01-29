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
	TDIR + "pier",
	TDIR + "lake1",
	TDIR + "sea0",
	TDIR + "sea2",
	TDIR + "sea3",
	TDIR + "sea4",
	SIGN_ROOM,
        TDIR + "sea4",
        TDIR + "sea3",
        TDIR + "sea2",
        TDIR + "sea1",
        TDIR + "lake2",
    }));

    set_time_between_stops(({
	24,
	3,
        4,
        7,
	3,
	3,
        24,
	3,
	3,
        7,
        4,
        3
    }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("large");
    add_adj("transport");
    set_long(break_string("This is a large ocean-going transport ship. " +
        "You see 15 oars sticking out on one side, and guess the number is " +
        "the same on the other side. The wooden ship looks very well " +
	"crafted. Some letters on the side of the ship indicates this " +
	"ship runs between Solace and Sparkle. " +
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

