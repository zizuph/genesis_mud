inherit "/d/Genesis/ship/ship";

#include "default.h"

void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(ROOM_DIR + "ship/cabin");
    set_deck(ROOM_DIR + "ship/deck");
    cap=clone_object(NPC_DIR + "humanoids/captain");
    set_captain(cap);
    set_places_to_go(({ROOM_DIR + "lake/pier",
		       ROOM_DIR + "lake/lake1",
		       ROOM_DIR + "lake/lake2",
		       ROOM_DIR + "lake/channel1",
		       ROOM_DIR + "lake/channel2",
		       ROOM_DIR + "lake/channel3",
		       ROOM_DIR + "mine/outside_beach",
		       "/d/Terel/ships/sea2",
		       "/d/Terel/ships/sea1",
		       "/d/Terel/ships/bay",
		       "/d/Terel/port/epier_s",
		       "/d/Terel/ships/bay",
		       "/d/Terel/ships/sea1",
		       "/d/Terel/ships/sea2",
		       ROOM_DIR + "mine/outside_beach",
		       ROOM_DIR + "lake/channel3",
		       ROOM_DIR + "lake/channel2",
		       ROOM_DIR + "lake/channel1",
		       ROOM_DIR + "lake/lake2",
		       ROOM_DIR + "lake/lake1"}));
    set_time_between_stops(({24,
			     2,
			     2,
			     2,
			     2,
			     2,
			     4,
			     2,
			     2,
			     2,
			     24,
			     2,
			     2,
			     2,
			     4,
			     2,
			     2,
			     2,
			     2,
			     2}));
    set_ticket_id("the emerald line");
    set_name("ship");
    add_name("boat");
    add_adj("nifty");
    set_long("A really neat ship.\n");
}
