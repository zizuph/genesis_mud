/* ship.c

   Modified:
   Oct 1997 by Fysix: adjusted board function for steeds.
   Ported to the new ship system by Tapakah, 06/2009
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

public void
create_ship()
{
  ::create_ship();
  set_cabin(CABIN);
  set_deck(DECK);

    set_name("ship");
    add_name("boat");
    add_adj("large");
    add_adj("merchant");
    set_long(break_string("Moored here is a large merchant ship, that currently " +
        "sails from Gondor to Kalad and back on a regular basis. Due to the " +
        "fear of Corsairs off the Gondorian coastline, the merchant ship "+
        "sails at irregular times. The boat looks like it has been sailing for "+
        "some years, but it still seems quite safe and sturdy. "+
       "There are various items, like ropes, lying here.\n", 78));
    enable_reset();
  set_ship_line(MASTER_OB(TO), CAPTAIN, TICKET,
                  ({ PELARGIR_PIER, GREY_HAVENS_PIER }));
}
