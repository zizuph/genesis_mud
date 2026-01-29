inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("halberd");
   add_name("drowwep");
   set_adj("black");
   add_adj("adamantine");
   set_long("A long-hafted polearm made completely out of solid "+
      "adamantine metal. It is truly a fusion of strength and beauty, a "+
      "trademark of drow craftsmanship.\n");
   set_hit(26);
   set_pen(38);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_VALUE, 450);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VOLUME,9000);
}
