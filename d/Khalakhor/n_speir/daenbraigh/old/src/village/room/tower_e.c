/*
 * East Tower - first floor
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

  add_exit("we_4","south",0);
  add_exit("tower_e2","up",0);
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
    "To the east you see path disappearing into the trees of the forest, " +
    "to the west you see more huts of the village, to the north you see "  +
    "tents of a camp and to the south you see just another hut across the "+
    "road.\n";
}

int *
query_local_coords()
{
  return ({-3,-1});
}
