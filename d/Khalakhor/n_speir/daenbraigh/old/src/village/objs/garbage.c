/*
 * Garbage pile to collect
 * TAPAKAH, 04/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include "../../daenbraigh.h"
#include "../../village/village.h"

#define MAXGARBAGE 300000

inherit "/d/Khalakhor/std/object";

void
create_khalakhor_object()
{
  ::create_khalakhor_object();

  set_name(V_OBJID + "_garbage");
  add_name(({"pile of garbage","garbage","pile"}));
  set_pname("piles of garbage");
  set_short("large pile of garbage");
  set_long("A large pile of garbage from a goblin village. You fail to "+
	   "distinguish anything specific within it.\n");

  add_prop(OBJ_I_VOLUME,random(MAXGARBAGE));
  add_prop(OBJ_I_WEIGHT,random(MAXGARBAGE));
  add_prop(OBJ_I_VALUE,1);
}
