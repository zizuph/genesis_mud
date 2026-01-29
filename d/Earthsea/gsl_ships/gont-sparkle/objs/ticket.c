
#include "/sys/stdproperties.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

#define TICKET_VALUE 30

inherit STDTICKET;

void
create_object()
{
    set_name("ticket");
    add_name("gontsparkle");
    set_short("feathery ticket");
    add_adj("feathery");
    set_long("This is a ticket for transport on a ship. "+
      "It looks very much like the feather of some bird, "+
      "however.\n");
  add_prop(OBJ_I_VALUE, TICKET_VALUE);
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 5);
  set_price(TICKET_VALUE);
}
