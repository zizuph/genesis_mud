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
    set_name("ticket");
    add_name("tharbadgreyhavens");
    add_adj("torn");
    add_adj("dirty");
    set_long("It looks like a ticket to the boatline between Tharbad\n"+
      "and Grey Havens.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 30);
    set_price(TICKET_PRICE);
}
