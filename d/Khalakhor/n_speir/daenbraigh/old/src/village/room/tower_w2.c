/*
 * West Tower - second floor
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

  add_exit("tower_w","down",0);
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
    "To the west you see the pier stretching into the sea. To the east is " +
    "the village and a path disappearing into the forest. To the south you "+
    "see a hut and the woody hills beyond it, and to the north you see the "+
    "fence and the seashore.\n";
}

int *
query_local_coords()
{
  return ({-7,-1});
}
