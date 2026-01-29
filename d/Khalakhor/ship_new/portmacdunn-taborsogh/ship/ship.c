/* File:          /d/Khalakhor/ship/macdunn/ansalon/ship.c
 * Creator:       Teth
 * Date:          April 13, 1997
 * Modifications:
 * Purpose:       This is the Macdunn-Kalaman, or Khalakhor-Ansalon
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 * Rerouted to Tabor Sogh as part of Hub initiative
 * Ported to the new ship system by Tapakah, 03/2009
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

public void
create_ship()
{
  ::create_ship();
  seteuid(getuid());

  set_cabin(({ CABIN, MAST }));
  set_deck(({ DECK, FORE }));
  set_name("galley");
  add_name(SHIP_NAME);
  add_name("ship");
  add_name("boat");
  add_adj("imposing");
  add_adj("wooden");
  set_long("This imposing wooden galley is the Bonnie Lass, a ship " +
           "that runs between the port towns of Port Macdunn and " +
           "Kalaman. It has a canvas sail, and no oars can be seen. " +
           "Its sturdy wooden structure allows it to survive ocean " +
           "storms.\n");
  add_item(({"sail","canvas sail"}),"It is aloft!\n");
  add_item(({"structure","sturdy structure","wooden structure"}),
           "The boat is made of sturdy white oak, a favoured wood of " +
           "shipwrights.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ MACDUNN_PIER, SOGH_PIER }) );
}
