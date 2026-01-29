#pragma strict_types
// name: Ticket   ~Avenir/common/ships/sparkle/ticket.c
// creator(s):    Tepisch  Oct 1994
// purpose:       Ticket for the Melancholy         
// last update:   Boriska, Mar 23 1995
// Ported by Tapakah to the new ship system, 05/2009
//
// * Lucius May 2009: Corrected porting, cleanups.
//
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDTICKET;
#define TICKET_PRICE 30

public void
create_object(void)
{
    set_name("ticket");
    add_name("_staek_ticket");
    add_adj("bone-coloured");
    set_long("Engraved into the polished bone ticket are the words:\n"+
      "The Good Ship Melancholy, providing transportation\n"+
      "   between the Rift of Sybarus and Sparkle town.\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    set_price(TICKET_PRICE);
}
