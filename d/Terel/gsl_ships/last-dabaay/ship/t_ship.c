#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIP;

public void
create_ship()
{
  ::create_ship();

  setuid();
  seteuid(getuid());
  set_deck(DECK);
  set_cabin(({CABIN, HOLD}));

  set_name("ship");
  add_name("boat");
  set_adj(({"large", "sailing"}));
  set_short("large sailing ship");
  set_long("It's a large sailing ship. On the side of the ship you " +
	   "read the name: " + SHIP_NAME + ".\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ DABAAY_PIER, LAST_PIER, }));
}

