#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();
  set_short("On the deck");
  set_long("You are standing on the deck of the small fishing boat. " +
	     "You can enter the cabin.\n");
  
  add_prop(ROOM_I_INSIDE,0);
  add_exit(CABIN, "cabin", 0);
  set_is_deck(1);
}


