inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("knife");
   add_name("drowwep");
   set_adj("black");
   add_adj("adamantine");
   set_pshort("black adamantine knives");
   set_long("A knife created from solid adamantine metal, its great "+
      "strength has been molded by a master craftsman into a fusion of "+
      "power with graceful beauty.\n");
   set_hit(11);
   set_pen(11);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE, 250);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
