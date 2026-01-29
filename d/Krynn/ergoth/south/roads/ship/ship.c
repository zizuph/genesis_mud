#include "local.h"

inherit "/d/Genesis/ship/ship";

void create_ship()
{
    seteuid(getuid());
    
    object cap = clone_object(CAPTAIN);
    set_captain(cap);
    
    set_name(SHIPNAME);
    add_name(({"ship", "vessel", "clipper"}));
    set_adj("small");
    set_short("small clipper");
    set_long("This small and narrow ship is designed for speed rather than "
        + "freight. Many lengths of rigging run to and from the ship's three "
        + "masts. You can see several sailors perparing the vessel for its "
        + "next voyage.\n");
    add_item("rigging", "A web of rope and chain is weaved across the ship, "
        + "giving the sailors control of their craft.\n");
    add_item(({"mast","masts"}), "Three masts rise from the deck, providing "
        + "support for the ship's many sails.\n");
    add_item(({"sail", "sails"}), "Despite several patches in plain sight, "
        + "the sails appear to be in good condition. They are quite clean "
        + "and billow pleasantly in the wind.\n");
    add_item(({"sailors"}), "Several sailors are busy preparing the ship "
        + "for departure.\n");
    
    set_ticket_id(TICKETNAME);
    set_deck(DECK);
    set_places_to_go(({
        DEST1,
        SEA + "sea1",
        SEA + "sea2",
        SEA + "sea3",
        SEA + "sea4",
        DEST2,
        SEA + "sea4",
        SEA + "sea3",
        SEA + "sea2",
        SEA + "sea1"
        }));
    set_time_between_stops(({
        20,
        3,2,1,2,
        20,
        3,2,1,2
        }));
}    
