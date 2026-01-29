inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("standard");
   add_adj("short");
   set_long("A typical example of a standard variety short sword. So "+
      "undistinguishable is the weapon that not a single marking or other "+
      "type of decoration can be found on it. The only thing of note is "+
      "its lack of upkeep, for the weapon is dull and worn.\n");
   set_hit(18);
   set_pen(19);
   set_wt(W_SWORD);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2500);
}
