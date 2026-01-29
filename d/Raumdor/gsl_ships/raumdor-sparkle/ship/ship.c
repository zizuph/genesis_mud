#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  ::create_ship();
  seteuid(getuid());
  set_deck(DECK);
  set_cabin(CABIN);
  set_name("barque");
  add_name("ship");
  set_adj("small");
  add_name("dreadnaught");
  set_long("You lay your eyes on a rather small and ancient looking "+
           "barque. It creaks and moans as the waves move it around in the "+
           "docks. On the mast you see a giant cross, and the head of an "+
           "angel adorns the prow.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ SPARKLE_PIER, RAUMDOR_PIER, }));
}

