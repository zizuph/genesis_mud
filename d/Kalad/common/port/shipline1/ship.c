inherit "/d/Genesis/ship/ship";
#include "../default.h"

void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_deck(PORT + "shipline1/upperdeck");
    set_cabin(PORT + "shipline1/cabin");
    cap = clone_object(PORT + "shipline1/captain");
    set_captain(cap);
    set_places_to_go(({PORT + "s81",
	PORT + "shipline1/sea",
	PORT + "shipline1/sea1",
	PORT + "shipline1/sea2",
	PORT + "shipline1/sea3",
	PORT + "shipline1/sea4",
	"/d/Shire/common/greyhaven/pier3",
	PORT + "shipline1/sea4",
	PORT + "shipline1/sea3",
	PORT + "shipline1/sea2",
	PORT + "shipline1/sea1",
	PORT + "shipline1/sea"}));
    set_time_between_stops(({24,
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
	4}));
    set_ticket_id("the kalad-shire line");
    set_name("ship");
    add_name("boat");
    set_adj("clipper");
    set_long("A magnificent clipper ship, its beauty astounds you.\n");
}

