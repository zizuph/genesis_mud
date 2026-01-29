#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDTICKET;

#define TICKET_PRICE 30

void
create_object()
{
  ::create_ticket();
    set_name("ticket");
    add_name("newbiesolacepelargir");
    add_adj("torn");
    set_long("It is a ticket for the boat that goes from Pelargir in Gondor to Solace, Gelan and Sparkle. Newbie only!\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, TICKET_PRICE);
	set_price(TICKET_PRICE);
}
