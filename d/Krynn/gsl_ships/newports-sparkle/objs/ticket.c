#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDTICKET;

#define TICKET_PRICE 30

void
create_object()
{
  ::create_ticket();
  set_name("ticket");
  add_name("newportssparkle");
  add_adj("red");
  set_long("It looks like a ticket to the merchantline between Newports " +
           "and Sparkle.\n");
  set_price(TICKET_PRICE);
  add_prop(OBJ_I_VALUE, TICKET_PRICE);
  add_prop(OBJ_I_WEIGHT, 20);
}

