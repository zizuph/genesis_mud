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

    set_name("airship");
    add_name(SHIP_NAME);
    add_name(({"zeppelin", "ship"}));
    add_adj("long");
    add_adj("leatherbound");
    set_long("This is a huge, leatherbound zeppelin, an airship with a long, "
        + "air-filled bladder keeping an open air cabin deck suspended "
        + "beneath it. The lower deck has glass ports for viewing, and "
        + "written in silver paint across its leather it says: Palanthas to "
        + "Sparkle\n");

    set_ship_line(MASTER_OB(TO),
                  CAPTAIN, TICKET,
                  ({ SPARKLE_PIER, PALANTHAS_PIER }));
}
