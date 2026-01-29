inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
/* by Korat */
create_weapon()
{
   ::create_weapon();
   set_name("pole");
   set_adj("wooden");
   set_long("This is a long wooden pole, mostly useful for "+
      "supporting your body for long walks, but also to "+
      "hit your opponent in case your trip were suddenly "+
      "halted by some nasty creatures.\n");
   set_hit(16);
   set_pen(8);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE, 400);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME, 3000);
}

