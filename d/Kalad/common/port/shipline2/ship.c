inherit "/d/Genesis/ship/ship";
#include "../default.h"

void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_deck(PORT + "shipline2/upperdeck");
    set_cabin(PORT + "shipline2/cabin");
    cap = clone_object(PORT + "shipline2/captain");
    set_captain(cap);
    set_places_to_go(({PORT + "s97",
	PORT + "shipline2/sea",
	PORT + "shipline2/sea1",
	PORT + "shipline2/sea2",
	PORT + "shipline2/sea3",
	PORT + "shipline2/sea4",
	PORT + "shipline2/sea5",
	PORT + "shipline2/sea6",
	"/d/Terel/ships/n_bay",
	"/d/Terel/n_port/pier2",
	"/d/Terel/ships/n_bay",
	PORT + "shipline2/sea6",
	PORT + "shipline2/sea5",
	PORT + "shipline2/sea4",
	PORT + "shipline2/sea3",
	PORT + "shipline2/sea2",
	PORT + "shipline2/sea1",
	PORT + "shipline2/sea"}));
    set_time_between_stops(({24,
	4,
	4,
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
	4,
	4,
	4}));
    set_ticket_id("the kalad-terel line");
    set_name("ship");
    add_name("boat");
    set_adj("spartan");
    set_long("A spartan and utilitarian ship, it looks rather plain.\n");
}

