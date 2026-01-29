#pragma strict_types

#include <stdproperties.h>
#include "../ship.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDTICKET;

#define TICKET_PRICE 12

public void
create_object()
{
  ::create_ticket();
    set_name("ticket");
    add_name("gontthwil");
    set_short("ticket");
    set_long("This is a ticket for transport on a ship. " +
        "It has a picture of a fiery red-scaled dragon " +
        "imprinted on the back.\n");
    add_prop(OBJ_I_VALUE, TICKET_PRICE);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 5);
    set_price(TICKET_PRICE);
}
