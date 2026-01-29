/*
 * Hut #7
 * TAPAKAH, 04/2005
 */

#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"
#include "../../nspeir.h"
#include "../../village/village.h"

inherit VILLAGEPATH + "hut";

void
create_khalakhor_room()
{
  ::create_gvillage_hut();

  add_exit("ns_4","west",0);
      
}
void
reset_room()
{
  ::reset_room();
}
