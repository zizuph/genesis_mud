inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   add_name("drowwep");
   set_adj("black");
   add_adj("adamantine");
   set_long("A sword produced from pure adamantine metal, its sheer "+
      "strength has been molded by a master craftsman into a fusion of "+
      "power with graceful beauty.\n");
   set_hit(29);
   set_pen(24);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,6000);
}
