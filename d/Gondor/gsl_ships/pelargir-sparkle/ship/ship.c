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

void
create_ship()
{
  ::create_ship();
    object cap;    
    set_cabin(CABIN);
    set_deck(DECK);

    set_name("ship");
    add_name("boat");
    add_name("cog");
    add_adj("large");
    add_adj("merchant");
    set_long("This is a large ocean-going merchant cog, built of strong wood. "+
      "You see 15 oars sticking out on one side, and guess the number is "+
      "the same on the other side. A large, whiteish sail is set above the "+
      "ship, and embroidered on the sail you see a white tree surrounded by "+
      "seven silver stars.\n");
    enable_reset();
    set_ship_line(MASTER_OB(TO), CAPTAIN, TICKET,
                  ({ SPARKLE_PIER, PELARGIR_PIER }));
}
