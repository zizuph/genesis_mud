#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  ::create_ship();
  setuid();
  seteuid(getuid());
  set_deck(DECK);
  set_cabin(({CABIN, PCABIN}));
  set_name("ship");
  add_name("boat");
  set_adj("clipper");
  set_long("A magnificent clipper ship, its beauty astounds you.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ SPARKLE_PIER, KABAL_PIER, }));
  
}

