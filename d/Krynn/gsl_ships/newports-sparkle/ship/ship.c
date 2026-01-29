#pragma save_binary

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  ::create_ship();
    set_cabin(({CABIN, ROWINGDECK}));
    set_deck(({DECK, FORE}));

    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("large");
    add_adj("transport");
    set_long("This is a large ocean-going transport ship. " +
             "You see 15 oars sticking out on one side, and guess the number is " +
             "the same on the other side. The wooden ship looks very well " +
             "crafted. Some letters on the side of the ship indicates this " +
             "ship runs between Newports and Sparkle.\n"
             );

    set_ship_line(MASTER_OB(TO),
                  CAPTAIN, TICKET,
                  ({ SPARKLE_PIER, NEWPORTS_PIER }));
}
