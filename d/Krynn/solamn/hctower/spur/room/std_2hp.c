// grace
// common 2hp functions, etc
// note: 

#include "../local.h"
#include "2hp.h"

inherit SPURRM;
inherit MAPPERRM;



void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);

  if (interactive(ob))
    start_room_tells();
}
