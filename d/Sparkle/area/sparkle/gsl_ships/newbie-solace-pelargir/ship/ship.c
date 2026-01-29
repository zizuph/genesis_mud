/* /d/Sparkle/area/sparkle/gsl_ships/newbie-solace-pelargir/ship/ship.c
 *
 * Adapted from Earendil's ship in Gondor
 * Tapakah, 05/2009
 */
#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit NEWBIE_SHIP;

void
create_ship()
{
   ::create_ship();
  set_cabin(CABIN);
  set_deck(DECK);

  set_name("ship");
  add_name("boat");
  add_name("vingilot");
  add_name("foam-flower");
  add_name("rothinzil");
  add_adj("slim");
  add_adj("sailing");
  set_long("This is the ship Vingilot, the Foam-flower. It is a beautiful " +
		   "ocean-going sailing ship, built of strong white wood. "+
		   "A large silver sail is set above the ship, and embroidered on the sail you see a golden star. "+
		   "The prow of the ship is fashioned like a swan.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ GELAN_PIER, SPARKLE_PIER,
                   SOLACE_PIER, PELARGIR_PIER, }) );
 
}

