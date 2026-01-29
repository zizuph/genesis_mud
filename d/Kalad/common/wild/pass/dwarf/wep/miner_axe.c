inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by korat */
create_weapon()
{
   ::create_weapon();
   set_name("pickaxe");
   add_name("axe");
   set_adj("miners");
   set_long("This axe is ment to be used for mining, rather "+
      "than warfare.\n");
   set_hit(20);
   set_pen(10);
   set_wt(W_AXE);
   set_hands(W_BOTH);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,200);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME, 6000);
}

