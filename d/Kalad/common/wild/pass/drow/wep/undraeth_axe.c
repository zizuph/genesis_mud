inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("axe");
   add_name("drowwep");
   set_adj("black");
   add_adj("adamantine");
   set_long("A gloriously-crafted waraxe, its design combines the "+
      "raw strength of adamantine metal with the fluid beauty of superb "+
      "drow craftsmanship.\n");
   set_hit(20);
   set_pen(29);
   set_wt(W_AXE);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,6000);
}
