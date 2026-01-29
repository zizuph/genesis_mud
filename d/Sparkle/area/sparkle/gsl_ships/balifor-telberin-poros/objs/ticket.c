#include "/sys/stdproperties.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDTICKET;

#define TICKET_PRICE 144

void
create_object()
{
  ::create_ticket();
    set_name("ticket");
    add_name("balifortelberinporos");
    set_short("ticket");
    set_long("This is a ticket for transport on a ship. "+
      "It has a picture of a fiery red-scaled dragon "+
      "imprinted on the back.\n");
    add_prop(OBJ_I_VALUE, TICKET_PRICE);
    add_prop(OBJ_M_NO_SELL, 1);
    set_price(TICKET_PRICE);
    
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
}
