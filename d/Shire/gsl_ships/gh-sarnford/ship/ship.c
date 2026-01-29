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
  set_cabin(({CABIN}));
  set_deck(({DECK}));

  set_name("ship");
  add_name("boat");
  add_adj("small");
  add_adj("slender");
  set_long("This small, slender ship rides eagerly on the waves.\n");

  set_ship_line(MASTER_OB(TO),
                 CAPTAIN, TICKET,
                 ({ SARNFORD_PIER, GREY_HAVENS_PIER }));
  
}

