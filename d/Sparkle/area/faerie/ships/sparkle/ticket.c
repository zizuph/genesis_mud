/*
 * Ticket for ship between Faerie and VK
 * -- Finwe, January 2006
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDTICKET;

void
create_object()
{
  ::create_ticket();
    set_name("ticket");
    add_name("_faerie_sparkle_ticket_");
    add_adj("yellow");
    set_long(
             "This ticket is valid for the boat that sails between " +
             "Faerie and Sparkle.\n"
             );

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 24);
    set_price(24);
}
