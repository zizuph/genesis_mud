/*
 *	/d/Gondor/common/ship/ship7.c
 *
 *	The ship running between Pelargir and Minas Tirith
 *
 *  Modified:
 *  Oct 1997 by Fysix: adjusted board function for steeds.
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
  set_cabin(CABIN);
  set_deck(DECK);
  set_name("boat");
  add_name("ship");
  set_adj(({"large", "river"}));
  set_long("This is a large river boat, built for traffic on the "
           + "Anduin. Its wide hull makes it a slow but safe means of "
           + "transportation. It is powered by oars and a large grey sail "
           + "on a single mast. On top of the sail, the banner of Pelargir "
           + "is flown. Written onto the bow is the name \"Anduilunte\".");
  enable_reset();
  set_ship_line(MASTER_OB(TO), CAPTAIN, TICKET,
                  ({ PELARGIR_PIER, HARLOND_PIER }));
}
