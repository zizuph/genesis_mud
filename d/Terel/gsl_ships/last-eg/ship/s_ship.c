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
  set_cabin(CABIN);

  set_name("boat");
  add_name("fishing boat");
  add_name("ship");
  set_adj("small");
  add_adj("fishing");
  set_long("A small fishing boat. Nowadays this fishing boat is " +
	   "used to transport people along the river.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ EG_PIER, LAST_PIER, }));
}
