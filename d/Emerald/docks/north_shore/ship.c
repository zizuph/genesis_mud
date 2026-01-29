inherit "/d/Genesis/ship/ship";

#include "../defs.h"
public void
create_ship()
{
    reset_euid();
    set_deck(DOCK_DIR + "north_shore/deck");
    /*
    set_cabin(DOCK_DIR + "north_shore/cabin");
    */
    set_captain(clone_object(DOCK_DIR + "north_shore/captain"));
    set_places_to_go(({ 
        DOCK_DIR + "north_shore/dock",

        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",

        "/d/Emerald/blackwall/delrimmon/trail/switchback1",

        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1" }));
    set_time_between_stops(({ 24, 2, 2, 2, 2, 2, 2, 24, 2, 2, 2, 2, 2, 2 }));
    set_ticket_id(NORTH_SHORE_LINE);

    set_name(({ "ferry", "boat", "ship" }));

    add_adj("grey");
    set_long("The grey ferry transports travellers between Ceral " +
        "Island and the northern shores of Lake Telberin.\n");
}
