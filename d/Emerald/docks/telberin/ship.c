inherit "/d/Genesis/ship/ship";

#include "../defs.h"
public void
create_ship()
{
    reset_euid();
    set_deck(DOCK_DIR + "telberin/deck");
    /*
    set_cabin(DOCK_DIR + "telberin/cabin");
    */
    set_captain(clone_object(DOCK_DIR + "telberin/captain"));
    set_places_to_go(({ 
        DOCK_DIR + "telberin/dock",

        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",

        "/d/Emerald/telberin/dock/telberin_dock",

        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
	  DOCK_DIR + "sea1" }));
    set_time_between_stops(({ 18, 2, 2, 2, 18, 2, 2, 2, 2 }));
    set_ticket_id(TELBERIN_LINE);

    set_name(({ "ferry", "boat", "ship" }));

    add_adj("green");
    set_long("The green ferry transports travellers between Ceral " +
        "Island and the mainland, just outside of Telberin.\n");
}
