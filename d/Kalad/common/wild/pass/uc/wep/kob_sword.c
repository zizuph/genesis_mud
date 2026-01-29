inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("filthy");
   add_adj("short");
   set_long("A rather plain short sword, the only noteworthy characteristic "+
      "of the weapon is that it is covered with feces.\n");
   set_hit(18);
   set_pen(19);
   set_wt(W_SWORD);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2500);
}
