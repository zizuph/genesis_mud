inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("gladius");
   set_adj("sharp");
   add_name("sword");
   set_long("This is a vicious weapon, made for stabbing the oponent "+
      "to death. When you touch the edge, blood starts to trickle; it is "+
      "very sharp!\n");
   set_hit(23);
   set_pen(16);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE, 250);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 1500);
}
