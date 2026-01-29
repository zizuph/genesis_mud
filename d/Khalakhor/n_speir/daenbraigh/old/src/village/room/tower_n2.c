/*
 * North Tower - second floor
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
  ::create_gvillage_tower("top");

  add_exit("tower_n","down",0);
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
    "To the west you see the village fence and the seashore, to the east "+
    "a military camp was erected edging into the tundra forest, to the south "+
    "you see the village stretching before you and to the north, beyond the "+
    "village fence and a strip of tundra you see wastelands stretching.\n";
}

int *
query_local_coords()
{
  return ({-5,-6});
}
