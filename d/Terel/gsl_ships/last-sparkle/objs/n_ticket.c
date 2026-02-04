#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

#define TICKET_VALUE 75

inherit STDTICKET;

public void
create_object()
{
  set_name("ticket");
  add_name("lastsparkle");
  add_adj("torn");
  set_long("It looks like a ticket to some ship.\n");
  add_prop(OBJ_I_VALUE, TICKET_VALUE);
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 5);
  set_price(TICKET_VALUE);
}
