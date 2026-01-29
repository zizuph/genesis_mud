inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("club");
   add_name("drowwep");
   set_adj("slim");
   add_adj("adamantine");
   set_long("A long, thin club of fine craftsmanship, fashioned from solid "+
      "adamantine.\n");
   set_hit(20);
   set_pen(17);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,800);
   add_prop(OBJ_I_WEIGHT,8000);
   add_prop(OBJ_I_VOLUME,8000);
}
