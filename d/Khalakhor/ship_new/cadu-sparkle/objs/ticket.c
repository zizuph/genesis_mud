/*
 * captain.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Ported to the new ship system by Tapakah, 10/2008
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

#define TICKET_VALUE 24

inherit STDTICKET;

void
create_object()
{
  ::create_ticket();
  set_name("ticket");
  add_name("CaduSparkle");
  set_adj(({"green"}));
  add_adj(({"green"}));
  set_long("This ticket is for the Cadu-Sparkle ship.\n");
  add_prop(OBJ_I_VALUE, TICKET_VALUE);
  add_prop(OBJ_M_NO_SELL, 1);
  add_prop(OBJ_I_NO_DROP, "@@flerp");
  set_price(TICKET_VALUE);
    
}

int
flerp()
{
    this_player()->catch_msg("Oh no! The ticket got all dirty! Now surely " +
                             "noone would buy it.\n");
    remove_prop(OBJ_I_VALUE);
    return 0;
}
