#pragma save_binary

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
   ::create_ship();

    seteuid(getuid());
    set_cabin(({CABIN, ROWINGDECK}));
    set_deck(({DECK, FORE}));

    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("rough");
    add_adj("merchant");
    set_long(break_string("This is a large, ocean-going merchant ship. " +
                          "You see 18 oars sticking out on one side, and guess the number is " +
                          "the same on the other side. The wooden ship looks very well " +
                          "crafted.\n", 70));
    set_ship_line(MASTER_OB(TO),
                  CAPTAIN, TICKET,
                  ({ SPARKLE_PIER, KALAMAN_PIER }));
}

