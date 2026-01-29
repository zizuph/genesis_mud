// Pickaxe for treasure hunter from dark tunnels
// Made by Boriska@Genesis, Nov 1994

inherit "/std/weapon";

#include <wa_types.h>

create_weapon ()
{
  set_name ("pickaxe");
  set_short ("handy pickaxe");
  set_long (
	  "Short and handy pickaxe, suitable for digging rocky ground.\n"
	    );
  set_wt (W_AXE);
  set_dt (W_SLASH | W_BLUDGEON);
  set_hit (10);
  set_pen (15);
  set_hands (W_ANYH);
}
