 /*  /d/Cirath/ships/kalad/ticket.c
  *  This is the ticket for the Tyr-Kalad boatline.
  *  Decius, November 1996
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
	add_name("tyr-kalad line");
   add_adj("filthy");
	add_adj("cloth");
	set_long("This filthy piece of cloth appears to be "+
		"a caravan ticket.\n");
	add_prop(OBJ_I_VALUE, 10);
   add_prop(OBJ_M_NO_SELL,1);
  }

