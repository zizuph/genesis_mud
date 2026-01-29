#pragma save_binary
#pragma strict_types

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
    add_name("pelargirgreyhavens");
    add_adj("torn");
    add_adj("brown");
    set_long("It looks like a ticket to the merchant ship running between Pelargir\n"+
      "in Gondor, and Grey Havens in Shire.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 28);
    set_price(TICKET_PRICE);
}
