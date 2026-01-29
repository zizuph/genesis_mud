 /*  /d/Cirath/ships/drakmere/ticket.c
  *  This is the ticket for the Tyr-Drakmere boatline.
  *  Decius, July 1997
  */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "ship.h"

void
create_object()
  {
	set_name("ticket");
	add_name("tyr-drakmere line");
        add_adj("ornate");
	add_adj("gold");
	set_long("This is an ornately carved wagon ticket made from "+
		"pure gold!\n");
	add_prop(OBJ_I_VALUE, 50);
        add_prop(OBJ_M_NO_SELL,1);
  }

