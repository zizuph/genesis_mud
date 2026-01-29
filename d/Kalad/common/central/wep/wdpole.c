inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
/* by Korat */
create_weapon()
{
   ::create_weapon();
   set_name("polearm");
   set_adj("wooden");
   set_long("This polearm is made of oak, and is only usefull as "+
      "a weapon to train with.\n");
   set_hit(5);
   set_pen(2);
   set_wt(W_POLEARM);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME,4000);
}

