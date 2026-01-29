/*
 * East Tower - second floor
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

  add_exit("tower_e","down",0);
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
  return BS("To the west the village opens to you and beyond it you catch a glimpse of the sea. " +
	    "To the east you see the forest and a well-trodden path going into it. To the north " +
	    "you notice a sort of a military camp beyond the trees and to the south you notice hills " +
	    "rising.\n");
}
