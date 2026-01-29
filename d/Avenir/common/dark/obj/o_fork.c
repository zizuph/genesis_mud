// Kitchen fork used by ogre mom for cooking and killing
// Made by Boriska@Genesis, Oct 1994

#include <wa_types.h>
#include <stdproperties.h>

inherit "/std/weapon";

create_weapon ()
{
  set_name("fork");
  add_adj("dirty");
  set_short ("dirty fork");
  set_long("Rusty dirty fork usually found in ogre kitchens.\n");
  
  set_wt(W_KNIFE);
  set_dt(W_IMPALE);
  
  set_hit(18);
  set_pen(15);
  
  add_prop (OBJ_I_WEIGHT, 4000);
}

