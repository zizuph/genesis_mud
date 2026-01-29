#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDTICKET;

#define TICKET_PRICE 18

void
create_object()
{
  ::create_ticket();
    set_name("ticket");
    add_name("pelargirharlond");
    add_adj("new");
    add_adj("blue");
    set_long("It looks like a ticket to the river boat running on the "
      + "Anduin between Pelargir and the Harlond, the harbour of Minas "
      + "Tirith.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 18);
    set_price(TICKET_PRICE);
}
