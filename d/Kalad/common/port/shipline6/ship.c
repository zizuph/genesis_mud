inherit "/d/Genesis/ship/ship";
#include "../default.h"

void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_deck(PORT + "shipline6/upperdeck");
    set_cabin(PORT + "shipline6/cabin");
    cap = clone_object(PORT + "shipline6/captain");
    set_captain(cap);
    set_places_to_go(({PORT + "s104",
	PORT + "shipline6/sea",
	PORT + "shipline6/sea1",
	PORT + "shipline6/sea2",
	PORT + "shipline6/sea3",
	PORT + "shipline6/sea4",
	"/d/Kalad/common/raum/wforest/dock3",
	PORT + "shipline6/sea4",
	PORT + "shipline6/sea3",
	PORT + "shipline6/sea2",
	PORT + "shipline6/sea1",
	PORT + "shipline6/sea"}));
    set_time_between_stops(({24,
	3,
	3,
	3,
	3,
	3,
	24,
	3,
	3,
	3,
	3,
	3}));
    set_ticket_id("the kabal-raumdor line");
    set_name("barque");
    add_name("ship");
    set_adj("small");
    set_long("You lay your eyes on a rather small and ancient looking "+
      "barque. It creaks and moans as the waves move it around in the "+
      "docks. On the mast you see a giant cross, and the head of an "+
      "angel adorns the prow.\n");
}

