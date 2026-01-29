#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDTICKET;

#define TICKET_PRICE 144

void
create_object()
{
  ::create_ticket();
    set_name("ticket");
    add_name("pelargirkalamangelan");
    add_adj("paper");
    set_long("This ticket is valid for the boatline between " +
             "Pelargir in Gondor, Kalaman in Krynn and Gelan in Calia.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, TICKET_PRICE);
    set_price(TICKET_PRICE);
}
