inherit "/d/Genesis/ship/ship";
#include "../default.h"

void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_deck(PORT + "shipline4/upperdeck");
    set_cabin(PORT + "shipline4/cabin");
    cap = clone_object(PORT + "shipline4/captain");
    set_captain(cap);
    set_places_to_go(({PORT + "s66",
	PORT + "shipline4/sea",
	PORT + "shipline4/sea1",
	PORT + "shipline4/sea2",
	"/d/City/common/pier/water3",
	"/d/City/common/pier/water2",
	"/d/City/common/pier/water1",
	"/d/City/common/pier/hor10",
	"/d/City/common/pier/water1",
	"/d/City/common/pier/water2",
	"/d/City/common/pier/water3",
	PORT + "shipline4/sea2",
	PORT + "shipline4/sea1",
	PORT + "shipline4/sea"}));
    set_time_between_stops(({24,
	4,
	4,
	4,
	4,
	4,
	4,
	24,
	4,
	4,
	4,
	4,
	4,
	4}));
    set_ticket_id("the kalad-city line");
    set_name("ship");
    add_name("boat");
    set_adj("transport");
    set_long("A massive transport ship that ferries travellers and cargo "+
      "between the city-states of Kabal and Arcoron.\n");
}

