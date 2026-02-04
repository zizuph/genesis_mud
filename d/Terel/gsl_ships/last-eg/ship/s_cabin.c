#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

public void
create_room()
{
  ::create_shiproom();
    add_prop(ROOM_I_INSIDE,1);
    set_short("The captain's cabin");
    set_long("The captain's cabin is rather spartan.\n");
    add_exit(DECK, "deck", 0);
}
