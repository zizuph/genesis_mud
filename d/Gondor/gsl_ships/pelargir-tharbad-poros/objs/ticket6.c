#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDTICKET;

#define TICKET_PRICE 36

public void
create_object()
{
  ::create_ticket();
    set_name("ticket");
    add_name("pelargirtharbadporos");
    add_adj("black");
    add_adj("dirty");
    set_long("It looks like a ticket to the corsair running from\n" +
      "the Fords of Poros to Lebennin and Tharbad.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 36);
    set_price(TICKET_PRICE);
}
