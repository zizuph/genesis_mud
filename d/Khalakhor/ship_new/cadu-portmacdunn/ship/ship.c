/* File:          /d/Khalakhor/ship/macdunn/shire/ship.c
 * Creator:       Teth
 * Date:          December 2, 1997
 * Modifications:
 * Purpose:       This is the Macdunn-Grey Havens, or Khalakhor-Shire
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
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
  //  if (!IS_CLONE)
  //  return;
  ::create_ship();
  seteuid(getuid());
  
  set_cabin(({ CABIN, MAST }));
  set_deck(({ DECK, FORE }));
  set_name("ship");
  add_name(SHIP_NAME);
  add_name("boat");
  add_name("vessel");
  add_adj("sickle-shaped");
  set_long("This sickle-shaped boat is the Corran, a ship " +
           "that travels between the village of Port Macdunn and the town " +
           "of Cadu. With the aft and fore sections of the vessel " +
           "jutting upward from out of the water, it looks rather " +
           "odd. A series of slim sails is attached to its mast.\n");
  add_item(({"sections","aft sections","fore sections"}),
           "They jut upwards from out of the water.\n");
  add_item(({"aft section","fore section","aft","fore"}),
           "It juts upward from out of the water, creating one " +
           "hook of the sickle-shape.\n");
  add_item("mast","The mast supports a small look-out.\n");
  add_item(({"look-out","small look-out"}),"The small " +
           "look-out is used to see far distances.\n");
  add_item(({"series of slim sails","series","slim sails",
             "sails"}),"The slim sails propel the ship to its " +
           "destinations.\n");
  add_item("sail","No particular one stands out.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ MACDUNN_PIER, CADU_PIER }) );
  
}
