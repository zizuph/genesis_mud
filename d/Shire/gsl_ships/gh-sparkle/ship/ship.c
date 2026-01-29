#pragma save_binary

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  ::create_ship();
  seteuid(getuid());
  set_cabin(({CABIN, CREWROOM}));
  set_deck(({DECK, PLATFORM}));

  set_name("ship");
  add_name("boat");
  add_adj("elegant");
  set_long("This is an elegant ship in perfect condition. A flying swan "+
           "is painted on its side.\n");
  set_ship_line(MASTER_OB(TO),
                 CAPTAIN, TICKET,
                 ({ SPARKLE_PIER, GREY_HAVENS_PIER }));
  
}

