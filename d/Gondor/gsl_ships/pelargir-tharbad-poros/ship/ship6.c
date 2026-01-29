/*
 *  A ship to run from the Fords of Poros to Pelargir upon Anduin,
 *  Tharbad upon Gwathlo, and back
 *
 *  Olorin, June 1995
 *
 *  Modified:
 *  Oct 1997 by Fysix: adjusted board function for steeds.
 *                     Prevent steeds from boarding this ship.
 *  Oct 2002 by Gwyneth: Removed prevention of steeds on this ship.
   Ported to the new ship system by Tapakah, 06/2009
   Due to a bug, route changed to circle Tharbad-Pelargir-Poros
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

  seteuid(getuid());
    set_name("corsair");
    set_short("small corsair");
    add_name(({"herifalmar", "ship", "boat", "vessel", }));
    add_adj(({"small", "run-down", }));
    set_long("This is a small sailing ship with a single mast with "
      + "a low keel so it can be used to sail up rivers. The ship is "
      + "rather old and a little shabby, but it does look to be in "
      + "good repair. The name 'Herifalmar' has been painted onto the bow.\n");
    enable_reset();
  set_ship_line(MASTER_OB(TO), CAPTAIN, TICKET,
                ({ POROS_PIER,
                   THARBAD_PIER, PELARGIR_PIER }));
  
    // Added by Fysix: don't allow steeds on this ship
    //set_no_allow_steed(1);
}

