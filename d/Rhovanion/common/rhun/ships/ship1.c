
#pragma save_binary

inherit "/d/Genesis/ship/ship";
#include "/d/Rhovanion/farlong.h"

void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(RHUN+"ships/cabin1");
    set_deck(RHUN+"ships/deck1");
    cap=clone_object(RHUN+"ships/captain1");
    set_captain(cap);
    set_places_to_go(({RHUN+"stown3/pier1",
			RHUN+"river/carnen1",
			RHUN+"river/carnen2",
			RHUN+"river/carnen3",
			RHUN+"river/carnen4",
			RHUN+"river/ih_pier",
			RHUN+"river/celduin1",
			RHUN+"river/celduin2",
			RHUN+"river/celduin3",
			RHUN+"river/celduin4",
			RHUN+"river/celduin5",
			RHUN+"river/esg_pier",
			RHUN+"river/celduin5",
			RHUN+"river/celduin4",
			RHUN+"river/celduin3",
			RHUN+"river/celduin2",
			RHUN+"river/celduin1",
			RHUN+"river/ih_pier",
			RHUN+"river/carnen4",
			RHUN+"river/carnen3",
			RHUN+"river/carnen2",
			RHUN+"river/carnen1"}));
    set_time_between_stops(({20,
			     2,
			     2,
			     2,
			     2,
			     15,
			     2,
			     2,
			     2,
			     2,
			     2,
			     20,
			     1,  /* well, now it sailes down the current */
			     1,
			     1,
			     1,
			     1,
			     15,
			     1,
			     1,
			     1,
			     1}));
    set_ticket_id("the Rhun-to-Esgaroth line");
    set_name("ship");
    add_name("boat");
    add_adj("wooden");
    set_long("This is a well-crafted wooden ship.\n");
}