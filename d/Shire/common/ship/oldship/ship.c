#pragma save_binary

inherit "/d/Genesis/ship/ship";
#include "/d/Shire/common/defs.h"

//#define ROKE_COVE_DIR "/d/Roke/varl/atuan/cape/"
#define ROKE_COVE_DIR "/d/Earthsea/ships/shire_line/"
///d/Earthsea/ships/shire_line/west_pier3

#define LOCAL_PIER "/d/Shire/common/greyhaven/pier2"

void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(SHIP_DIR + "oldship/cabin");
    set_deck(SHIP_DIR + "oldship/deck");
    cap = clone_object(SHIP_DIR + "oldship/iarwain");
    set_captain(cap);
    set_places_to_go(({LOCAL_PIER,
                       SHIP_DIR + "w6",
		                     SHIP_DIR + "w5",
                       SHIP_DIR + "w4",
                       SHIP_DIR + "w3",
                       SHIP_DIR + "w2",
                       SHIP_DIR + "w1",
//                       ROKE_COVE_DIR + "pier1",
                        ROKE_COVE_DIR + "west_pier3",
                       SHIP_DIR + "w1",
                       SHIP_DIR + "w2",
                       SHIP_DIR + "w3",
                       SHIP_DIR + "w4",
                       SHIP_DIR + "w5",
                       SHIP_DIR + "w6",}));

  set_time_between_stops(({20,2,4,2,3,3,3,20,3,3,3,2,4,2}));

    set_name("ship");
    add_name("boat");
    add_adj("old");
    set_ticket_id("the Mithlond-Gont line");
    set_long("This is an old ship in poor condition.\n");
}