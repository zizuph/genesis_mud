/*
 * Path to hammerhands, #7
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

  add_exit("path6","northwest");
  add_exit("path8","south");
  
}

void
init()
{
  ::init();
}
