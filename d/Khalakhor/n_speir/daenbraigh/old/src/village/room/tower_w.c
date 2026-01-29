/*
 * West Tower - first floor
 * TAPAKAH, 04/2005
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

  add_exit("we_1","south",0);
  add_exit("tower_w2","up",0);
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
    "To the west you see the seashore. To the east you see the entrance to " +
    "the shop. To the south you see the track going before a hut and to the "+
    "north you see the fence that surrounds the village.\n";
}

int *
query_local_coords()
{
  return ({-7,-1});
}
