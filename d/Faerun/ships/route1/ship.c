inherit "/d/Genesis/ship/ship";

#define SHIP_DIR  "/d/Faerun/ships/"

#include "../../defs.h"


public void
create_ship()
{
    reset_euid();
    set_cabin(SHIP_DIR +"route1/cabin");
    set_deck(SHIP_DIR + "route1/deck");
    set_captain(clone_object(SHIP_DIR + "route1/captain"));
    set_places_to_go(({ P_WATERDEEP_CASTLEWARD + "harbour/harbour3",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        "/d/Avenir/common/port/port16",
        //P_WATERDEEP_CASTLEWARD + "harbour/harbour5",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1",
        SHIP_DIR + "route1/sea1" }));
    set_time_between_stops(({ 24,2,2,2,2,2,2,2,2,2,24,2,2,2,2,2,2,2,2,2}));
    set_ticket_id("Faerun1");
    set_name("sloop");
    add_name("_ship1");
    add_name("boat");
    add_name("ship");
    set_adj("white");
    add_adj("fast");
    
    set_long("It is a white fast sloop with the letters 'Brevari' painted with " +
    "purple colour on its side. Its apparently build for great speed and for easy maneouvering " +
    "on the high sea, though even for its small size it can still carry alot of " +
    "passengers and some cargo.\n");
}
