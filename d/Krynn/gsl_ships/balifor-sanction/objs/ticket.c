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
    add_name("baliforsanction");
    set_adj("blue");
    add_adj("dragon-marked");
    set_long("The ticket is blue and marked with a five-headed dragon. " +
        "It appears to give passage between Port Balifor and Sanction.\n");
  set_price(TICKET_PRICE);
  add_prop(OBJ_I_VALUE, TICKET_PRICE);
}
