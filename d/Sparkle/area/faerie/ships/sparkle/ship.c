/*
 * Ship between Faerie and Sparkle
 * The first brand new ship of the new system
 * Tapakah, 10/2008
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "../../rooms/forest/_defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIP;

#define SPARKLE_PIER    "/d/Genesis/start/human/town/pier15"
#define FAERIE_PIER     "/d/Sparkle/area/faerie/rooms/forest/pier00"

void
create_ship()
{
    set_ship_line(MASTER_OB(this_object()), 
                  SP_SHIP_DIR + "captain",
                  SP_SHIP_DIR + "ticket", 
                  ({ FAERIE_PIER, 
                     SPARKLE_PIER }) );             
    
  if (!IS_CLONE)
    return;

  ::create_ship();

  seteuid(getuid());

  set_cabin(SP_SHIP_DIR + "cabin");
  set_deck(SP_SHIP_DIR + "deck");

  set_name("boat");
  add_name("ship");
  add_adj("white");
  add_adj("oblong");
  set_long("This oblong white boat sails between Faerie and Sparkle City. "+
           "It is a medium-size vessel built for cabotage operations. " +
           "It is a property of Genesis ShipLines Company.\n");           
}
