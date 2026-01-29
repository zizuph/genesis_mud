// Iron pole found in
// Can be used as weapon and for lifting rock slab to enter worm lair.
// Made by Boriska Jan 1995

inherit "/std/weapon";

#define POLE_ID "worm_lair_entrance_pole"
// should match the ID in l4/n26

#include <wa_types.h>
#include <stdproperties.h>

create_weapon ()
{
  set_name ("pole");
  add_name (POLE_ID);
  set_short ("iron pole");
  set_long (
     "Crude and heavy iron pole covered with rust.\n"
	    );
  set_wt (W_POLEARM);
  set_dt (W_BLUDGEON);
  set_hit (10);
  set_pen (10);
  set_hands (W_ANYH);
  add_prop (OBJ_I_WEIGHT, 30000);
  add_prop (OBJ_I_VOLUME, 10000);
}


