inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

void create_object()
{
  set_name("map");
  set_adj(({"heavily", "marked"}));
  set_long("You look at the map closely and notice that it is a map of " +
	   "Gont. A big red X has been crossed on a city on the east side " +
	   "of the island. You see two black circles around what looks like " +
	   "Gont Port and a village in the mountains. Pointing to the " +
	   "circles are four arrows, two from somewhere in the mountains " +
	   "and two from somewhere along the coastline.\n");
  add_prop(OBJ_I_VALUE, 50);
  add_prop(OBJ_I_WEIGHT, 100);
  add_prop(OBJ_I_VOLUME, 10);
  add_prop(OBJ_M_NO_BUY, 1);
  set_keep(1);
}

int is_karg_map()
{
  return 1;
}
