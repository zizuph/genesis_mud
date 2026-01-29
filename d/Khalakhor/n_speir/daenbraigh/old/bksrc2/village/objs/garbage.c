/*
 * Garbage pile to collect
 * TAPAKAH, 04/2005
 */

inherit "/d/Khalakhor/std/object";

#include "../../nspeir.h"
#include <stdproperties.h>

#define MAXGARBAGE 300000

void
create_khalakhor_object()
{
  ::create_khalakhor_object();

  set_name("pile of garbage");
  add_name("garbage");
  add_name("pile");
  set_pname("piles of garbage");
  set_long(BSN("A large pile of garbage from a goblin village. You fail to "+
	       "distinguish anything specific within it."));

  add_prop(OBJ_I_VOLUME,random(MAXGARBAGE));
  add_prop(OBJ_I_WEIGHT,random(MAXGARBAGE));
  add_prop(OBJ_I_VALUE,1);
}
