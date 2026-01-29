/* File:          /d/Khalakhor/ship/macdunn/calia/ship.c
 * Creator:       Teth
 * Date:          April 15, 1997
 * Modifications: November 11, 1997, Teth, added support
 * Purpose:       This is the Macdunn-Gelan, or Khalakhor-Calia
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/calia/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit NEWBIE_SHIP;

public void
create_ship()
{
  ::create_ship();
  set_deck(DECK);
  set_name("boat");
  add_name(SHIP_NAME);
  add_name("ship");
  add_adj("fishing");
  set_long("This fishing boat is the Cuinnsear, a dagger-shaped " +
           "fishing vessel that transports small people around Sparkle, Gelan " +
           "Cadu and Enchanted Garden in Terel. Although small, this ship does " +
           "appear to be able to withstand an ocean storm, because of " +
           "its unique shape.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ SPARKLE_PIER, GELAN_PIER,
                   CADU_PIER, ENCHANTED_GARDEN_PIER }) );
  
}
