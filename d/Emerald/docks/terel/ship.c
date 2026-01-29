inherit "/d/Genesis/ship/ship";

#include "../defs.h"

#define TEREL_S_DIR "/d/Terel/ships/"
#define TEREL_P_DIR "/d/Terel/port/"

public void
create_ship()
{
    reset_euid();
    set_cabin(DOCK_DIR + "terel/cabin");
    set_deck(DOCK_DIR + "terel/deck");
    set_captain(clone_object(DOCK_DIR + "terel/captain"));
    set_places_to_go(({ DOCK_DIR + "terel/dock",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        TEREL_S_DIR + "sea2",
        TEREL_S_DIR + "sea1",
        TEREL_S_DIR + "bay",
        "/d/Terel/dabaay/harbor/npier_3",
        TEREL_S_DIR + "bay",
        TEREL_S_DIR + "sea1",
        TEREL_S_DIR + "sea2",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1" }));
set_time_between_stops(({ 24,2,2,2,2,2,2,2,2,24,2,2,2,2,2,2,2,2}));
    set_ticket_id("the emerald line2");
    set_name("ship");
    add_name("boat");
    add_adj("nifty");
    set_long("A really neat ship.\n");
}
