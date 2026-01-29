// Table spoon used by ogre mom for cooking and feasts
// Made by Boriska@Genesis, Oct 1994

#include <wa_types.h>
#include <stdproperties.h>

inherit "/std/weapon";

create_weapon ()
{
  set_name("spoon");
  add_adj("table");
  set_short ("table spoon");
  set_long("Disguisting gigantic spoon from ogre dining room.\n");
  
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  
  set_hit(20);
  set_pen(23);
  
  add_prop (OBJ_I_WEIGHT, 6000);
}
