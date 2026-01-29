inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("example");
   set_hit(10);
   set_pen(15);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
   add_prop(OBJ_I_VALUE,50);
}
