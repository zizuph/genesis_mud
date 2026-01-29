inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name(({"axe","battleaxe"}));
   set_adj("large");
   add_adj("shining");
   set_long("This battleaxe has been taken well care of by its "+
      "former owner. Every inch of metal has been carefully waxed "+
      "and polished, making it shine. On the side of the sharp blade "+
      "an insigna of the former owner can be seen: Karoth.\n");
   set_hit(23);
   set_pen(36);
   set_hands(W_BOTH);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE, 650);
   add_prop(OBJ_I_WEIGHT,20000);
   add_prop(OBJ_I_VOLUME,20000);
}

