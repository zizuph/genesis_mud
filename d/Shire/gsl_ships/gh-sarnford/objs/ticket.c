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
    add_name("greyhavenssarnford");
    add_adj("brown");
    add_adj("paper");
    set_long("This is a ticket for 'The Osprey', a ship which travels "
        + "a regular route between the Grey Havens and Sarn Ford.\n");
    add_prop(OBJ_I_VALUE, TICKET_PRICE);
    set_price(TICKET_PRICE);
}
