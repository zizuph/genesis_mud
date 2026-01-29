inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("axe");
   set_adj("filthy");
   add_adj("long-hafted");
   set_long("A double-bladed axe mounted upon a long, thin wooden haft. "+
      "Although in relatively good condition, it is covered with feces.\n");
   set_hit(22);
   set_pen(29);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,300);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
}
