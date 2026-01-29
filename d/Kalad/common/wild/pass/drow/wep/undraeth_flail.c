inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("flail");
   add_name("drowwep");
   set_adj("black");
   add_adj("adamantine");
   set_long("A multi-headed flail made totally from pure and untainted "+
      "adamantine metal. It is truly a fusion of strength and beauty, a "+
      "trademark of superb drow craftsmanship.\n");
   set_hit(20);
   set_pen(15);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE, 400);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,6000);
}
