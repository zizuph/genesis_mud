inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("mace");
   add_name("drowwep");
   set_adj("exquisite");
   add_adj("adamantine");
   set_long("A mace of exquisite craftsmanship fashioned from solid "+
      "adamantine.\n");
   set_hit(29);
   set_pen(20);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,1000);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,10000);
}
