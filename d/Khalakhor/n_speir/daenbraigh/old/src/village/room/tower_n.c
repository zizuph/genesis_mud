/*
 * North Tower - first floor
 * TAPAKAH, 05/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit V_TOWER_BASE;

void
create_khalakhor_room()
{
  ::create_gvillage_tower("ground");

  add_exit("ns_1","south",0);
  add_exit("tower_n2","up",0);
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
  return
    "To the west and to the north you see the village fence, to the east "+
    "is the entrance to a military camp was erected edging into the tundra "+
    "forest, and to the south you see a path going towards the smithy.\n";
}

int *
query_local_coords()
{
  return ({-5,-6});
}
