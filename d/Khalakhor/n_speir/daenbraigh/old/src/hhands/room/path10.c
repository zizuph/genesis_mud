/*
 * Path to hammerhands, #10, before the guild
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

  set_long(query_long() +
	   "A clearing with a large building opens to the southeast.\n");

  add_exit("path9","northwest");
  add_exit("entrance1","southeast");
  
}

void
init()
{
  ::init();
}
