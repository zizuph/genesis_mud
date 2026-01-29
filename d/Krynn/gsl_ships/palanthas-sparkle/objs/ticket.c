#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDTICKET;

#define TICKET_PRICE 12

void
create_object()
{
  ::create_ticket();
  set_name("ticket");
  add_name("palanthassparkle");
  add_adj("marble");
  add_adj("winged");
  set_long("Grey with mottled white, this ticket almost looks like marble. It "
    + "is shaped like a wing and reads: Palanthas - Sparkle: Admit One.\n");
  set_price(TICKET_PRICE);
  add_prop(OBJ_I_VALUE, TICKET_PRICE);
  add_prop(OBJ_I_WEIGHT, 10);
}

