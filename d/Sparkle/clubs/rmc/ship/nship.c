/*
 * Ported to the new ship system and rerouted to Sparkle
 * Tapakah, 10/2008
 */

#pragma save_binary

#include "defs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include <macros.h>

inherit STDSHIP;

#define            SPARKLE_PIER "/d/Genesis/start/human/town/pier14"
#define            GOLDEN_ISLAND_PIER (RMCROOMS + "pier")

void
create_ship()
{
  set_ship_line(MASTER_OB(this_object()), 
                RMCNPC + "ncaptain",
                RMCOBJ + "gticket", 
                ({ SPARKLE_PIER, 
                   GOLDEN_ISLAND_PIER }) );               
    
  if (!IS_CLONE)
    return;
  FIXEUID;

  ::create_ship();
  set_deck(RMCSHIP+"gdeck");
  set_cabin(RMCSHIP+"gcabin");

  set_name("ship");
  add_name("boat");
  set_adj("golden");
  add_adj("large");
  
  set_short("large golden ship");
  set_long(
    "This is a very impressive ship. It is large and is covered with gold. "+
    "The elegance it shows, lying in the water, has no competitor in this "+
    "world. The owner of this ship is obviously very rich, since he can afford "+
    "it. You can also see the logo of the Rich Men's Club on the side of the "+
    "ship.\n");
}
