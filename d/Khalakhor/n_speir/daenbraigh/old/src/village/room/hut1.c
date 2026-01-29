/*
 * Hut #1
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit V_HUT_BASE;
inherit DAENBRAIGH_BASE;

void
create_khalakhor_room()
{
  ::create_gvillage_hut();

  add_exit("we_3","south",0);
  add_object(V_CART);
}

void
reset_room()
{
  ::reset_room();
}

int *
query_local_coords()
{
  return ({-4,-1});
}
