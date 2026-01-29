inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
/* by Korat */
create_weapon()
{
   ::create_weapon();
   set_name("club");
   set_adj("wooden");
   set_long("This club is made of oak, and is used for "+
      "training purposes. It can do some damage though.\n");
   set_hit(10);
   set_pen(20);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME,4000);
}

