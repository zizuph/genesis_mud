/*
* Creator: Shadowlynx
* Date   : February/98
* File   : ticket.c
* Updated:
* By Whom:
*/

/* Ticket for the Palanthas - Sancrist shipline */
inherit "/std/object";
#include "../local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("stained");
    add_adj("paper");
    set_long("It looks like a boarding ticket for Chislev's" +
      " Whisper. A shipline between Palanthas and Sancrist.\n");
    add_prop(OBJ_I_VALUE, 24);

 /* The stained ticket can have one out of four different stains */
    add_item( ({ "stain", "stains" }), "It looks like a " + ({"blood", "oil", "grease", "coffee" })[random(4)] + " stain.\n");
}

