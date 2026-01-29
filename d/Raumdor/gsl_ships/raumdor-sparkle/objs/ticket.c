#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

#define TICKET_VALUE 24

inherit STDTICKET;

void
create_object()
{
    set_name("ticket");
    add_name("raumdorsparkle");
    set_adj("tattered");
    set_short("tattered ticket");
    set_long("It looks like a ticket for the Sparkle - Raumdor shipline.\n");
    add_prop(OBJ_I_VALUE, TICKET_VALUE);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 5);
  set_price(TICKET_VALUE);
}

