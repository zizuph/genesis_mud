#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();
  add_prop(ROOM_I_INSIDE,1);
  set_short("Captain's Cabin");
  set_long("This is a small near-empty cabin. There is only a "+
           "small table in the corner, a bed on the wall, and a tiny "+
           "window from which you can see outside into the sea.\n");
  add_item("bed","A very comfortable looking bed.\n");
  add_item("table","A holy symbol, some maps, and some pens "+
           "lay on it.\n");
  add_item("window","You see the rolling waves outside.\n");
  add_exit(DECK, "out");
}

