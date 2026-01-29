inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
/* by Korat */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("wooden");
   set_long("This sword is made of oak, and is only usefull as "+
      "a weapon to train with.\n");
   set_hit(3);
   set_pen(3);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME,4000);
}

