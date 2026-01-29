// Wooden stick - poor club weapon, found on the ground in dark/l4/n31
// Made by Boriska, Dec 1994

#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/weapon";

create_weapon()
{
  set_name ("stick");
  set_short ("wooden stick");
  set_long (
  "A simple wooden stick made from oak. It can be used as a poor weapon.\n");

  set_wt(W_CLUB);
  set_hit(9);
  set_pen(9);
  set_hands (W_ANYH);
  
  add_prop (OBJ_I_WEIGHT, 5000);
  add_prop (OBJ_I_VOLUME, 5000);
}
