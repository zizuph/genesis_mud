inherit "/d/Genesis/ship/ship";
#include "../default.h"

void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_deck(PORT + "shipline5/upperdeck");
    set_cabin(PORT + "shipline5/cabin");
    cap = clone_object(PORT + "shipline5/captain");
    set_captain(cap);
    set_places_to_go(({PORT + "s1",
	PORT + "shipline5/sea",
	PORT + "shipline5/sea1",
	PORT + "shipline5/sea2",
	PORT + "shipline5/sea3",
	PORT + "shipline5/sea4",
	"/d/Emerald/lake/pier6.c",
	PORT + "shipline5/sea4",
	PORT + "shipline5/sea3",
	PORT + "shipline5/sea2",
	PORT + "shipline5/sea1",
	PORT + "shipline5/sea"}));
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
    set_ticket_id("the kalad-emerald line");
    set_name("ship");
    add_name("boat");
    set_adj("passage");
    set_long("A far-travelling passage vessel.\n");
}

