/*
 * South Tower - second floor
 * TAPAKAH, 05/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "../../nspeir.h"
#include "../../village/village.h"

inherit VILLAGEPATH + "tower";

void
create_khalakhor_room()
{
  ::create_gvillage_tower("top");

  add_exit("tower_s","down",0);
  reset_room();
}
void
init()
{
  ::init();
}
string
query_view()
{
  return BS("To the west you catch a glimpse of sea beyond the hills and an outline of a pier. " +
	    "To the east you see the forest meeting the hills and some kind of smoke beyond it. " +
	    "To the north the village and a kind of military camp can be seen while to the south " +
	    "you only see hills rising steeply before the tower.\n");
}
