// Pole.c for the gatekeeper

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>

create_weapon ()
{
  set_name ("pole");
  set_short ("long wooden pole");
  set_adj("long");
  add_adj("wooden");
  set_long ("This is a long pole that can be used as a weapon, although "
     +"it won't do a lot of damage.\n");
  set_wt (W_POLEARM);
  set_dt (W_SLASH);
  set_hit (10);
  set_pen (15);
  set_hands (W_ANYH);
}

