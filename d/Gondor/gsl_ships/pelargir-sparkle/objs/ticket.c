#pragma save_binary
#pragma strict_types

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
    add_name("the Gondorian line");
    add_adj("torn");
    set_long("It looks like a ticket to the boatline between Pelargir\n"+
      "and Sparkle.\n");
    add_prop(OBJ_I_VALUE, 30);
    set_price(TICKET_PRICE);
}
