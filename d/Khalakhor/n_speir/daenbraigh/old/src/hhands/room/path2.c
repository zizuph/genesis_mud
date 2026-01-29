/*
 * Path to hammerhands, #2
 * TAPAKAH 10/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

inherit HH_PATH_BASE;

void
create_khalakhor_room()
{
  ::create_hhands_path();

  add_exit("path1","northwest");
  add_exit("path3","south");
  
}

void
init()
{
  ::init();
}
