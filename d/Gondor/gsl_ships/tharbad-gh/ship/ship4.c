/* ship4.c

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
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);

    set_name("ship");
    add_name("boat");
    add_adj("old");
    add_adj("corsair");
    set_long("This is an old corsair ship, rather run-down and in a"
             + " state of disrepair. Nevertheless, it looks like it"
             + " still has the ability to weather the open seas. A"
             + " dozen or so oars stick out from the sides of the"
             + " mighty hull, and a mighty grey sail is set above the"
             + " prow.\n");
    enable_reset();
    set_ship_line(MASTER_OB(TO), CAPTAIN, TICKET,
                  ({ THARBAD_PIER, GREY_HAVENS_PIER }));
}
