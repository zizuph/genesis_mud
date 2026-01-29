/* Adapted from Gondor - Gont shipline
   Tapakah, 05/2009
 */

#pragma save_binary
#pragma strict_types

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  ::create_ship();
  setuid();
  seteuid(getuid());
  set_cabin(CABIN);
  set_deck(DECK);
  set_name("ship");
  add_name("boat");
  add_adj("large");
  add_adj("sailing");
  set_long("Moored here is a large sailing ship, that currently " +
           "sails from Gont Port to Gondor and back on a regular basis. "+
           "Due to the " +
           "fact that the captain has to make sure whether he will encounter " +
           "any pirates during the long trip, you never know when the ship " +
           "arrives and leaves. The boat itself made of wood and looks quite " +
           "new. There are various items, like ropes, lying here.\n");
  set_ship_line(MASTER_OB(TO), CAPTAIN, TICKET,
                ({ PELARGIR_PIER, KALAMAN_PIER, GELAN_PIER }) );
}
