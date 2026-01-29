// Hammer for goblin digger from dark tunnels, used by dark/l4/t_goblin
// Made by Boriska, Feb 28 1994

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon ()
{
  set_name ("hammer");
  set_short ("plain hammer");
  add_adj("plain");
  set_long (
	    "Its a mining tool, quite old and in bad condition. It could\n"+
	    "be used as weapon as well.\n");
  set_wt (W_CLUB);
  set_dt (W_BLUDGEON);
  set_hit (10);
  set_pen (15);
  set_hands (W_ANYH);
  add_prop(OBJ_I_WEIGHT, 8000);
  add_prop(OBJ_I_VOLUME, 3000);
}
