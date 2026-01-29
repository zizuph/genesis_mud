/*
 * Path to hammerhands, #1
 * TAPAKAH 10/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"
#include "../../village/village.h"

inherit HH_PATH_BASE;

void
create_khalakhor_room()
{
  ::create_hhands_path();

  set_long(query_long() + "A clearing with a village opens to the west.\n");

  add_exit(V_ROOM + "we_4","west");
  add_exit("path2","southeast");
  
}
void
init()
{
  ::init();
}
