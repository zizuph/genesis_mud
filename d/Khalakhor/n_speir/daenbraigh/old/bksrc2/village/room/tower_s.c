/*
 * South Tower - first floor
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
  ::create_gvillage_tower("ground");

  add_exit("ns_4","north",0);
  add_exit("tower_s2","up",0);
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
  return BS("To the east and to the south you see the village fence, to the west a mighty forest rises "+
	    " and to the north a path runs into the village in between two huts.");
}
