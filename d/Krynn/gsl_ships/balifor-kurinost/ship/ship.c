inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_callout_fq(4);
    set_places_to_go(({
    PIER,
    ROOM + "sea3",
    ROOM + "sea2",
    ROOM + "sea1",

	PIER2,
	ROOM + "sea1",
	ROOM + "sea2",
	ROOM + "sea3",
      }));

    set_time_between_stops(({
        13,
	4,
	5,
        3,
        13,
        5,
        4,
        4,
      }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("green");
    add_adj("transport");
    set_long("This ship is decorated with marks of the Green Dragonarmy. "+
        "It is used to transport troops and equipment across the Bay "+
        "of Balifor.\n");
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

