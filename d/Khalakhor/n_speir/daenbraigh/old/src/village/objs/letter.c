/*
 * Courier's letter
 * TAPAKAH, 03/2007
 */

#pragma strict_types

#include <stdproperties.h>
#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit "/d/Khalakhor/std/object";

void
create_khalakhor_object()
{
  ::create_khalakhor_object();
  set_name(V_OBJID + "_letter");
  add_name(({"letter"}));
  set_short("wrinkled smelly letter");
  set_long("This letter is fully covered with small letters written by a " +
	   "steady, learned hand. Surprisingly you manage to read most of "+
	   "it and realize it is about the upcoming offense prepared by "  +
	   "Daenbraigh army onto the human settlements in vicinity of "    +
	   "Port Macdunn.\n");

  add_prop(OBJ_I_VOLUME,5);
  add_prop(OBJ_I_WEIGHT,5);
  add_prop(OBJ_I_VALUE,0);
   
}
