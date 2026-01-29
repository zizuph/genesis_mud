// Shovel used by archaelogist from dark tunnels
// Made by Boriska@Genesis, Nov 1994

inherit "/std/weapon";

#include <wa_types.h>

create_weapon ()
{
  set_name ("shovel");
  set_short ("short shovel");
  set_long (
	  "Short and light shovel, suitable for carrying in long journeys.\n"
	    );
  set_wt (W_POLEARM);
  set_dt (W_SLASH);
  set_hit (10);
  set_pen (15);
  set_hands (W_ANYH);
}
