  /* /d/Cirath/ships/roke/ticket.c
  * This is the ticket for the Tyr-Roke shipline.
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
    add_name("tyr-roke line");
    add_adj("carved");
    add_adj("chitin");
    set_long("This is a piece of bone with two images carved into "+
      "it. One of a pair of crossed axes, and the other of a "+
      "robed man wearing a crown.\n");
	add_prop(OBJ_I_VALUE, 10);
   add_prop(OBJ_M_NO_SELL,1);
  }

