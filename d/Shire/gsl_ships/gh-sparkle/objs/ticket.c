#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDTICKET;

#define TICKET_PRICE 20

void
create_object()
{
  ::create_ticket();
    set_name("ticket");
    add_name("greyhavenssparkle");
    add_adj("torn");
    set_long("This is a ticket for the boat between Sparkle and Grey Havens.\n");
    add_prop(OBJ_I_VALUE, TICKET_PRICE);
  set_price(TICKET_PRICE);
}
