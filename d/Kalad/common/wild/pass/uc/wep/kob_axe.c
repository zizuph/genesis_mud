inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("axe");
   set_adj("filthy");
   add_adj("hand");
   set_long("A typical hand axe, the only noteworthy characteristic of "+
      "which is that it is covered with feces.\n");
   set_hit(15);
   set_pen(19);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2500);
}
