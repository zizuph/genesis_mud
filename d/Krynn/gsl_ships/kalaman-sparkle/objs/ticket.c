#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDTICKET;

#define TICKET_PRICE 28

void
create_object()
{
  ::create_ticket();
  set_name("ticket");
  add_name("kalamansparkle");
  add_adj("nice");
  add_adj("paper");
  set_long("It looks like a ticket to the merchantline between Kalaman\n"+
           "and Sparkle.\n");
  set_price(TICKET_PRICE);
  add_prop(OBJ_I_VALUE, TICKET_PRICE);
}
