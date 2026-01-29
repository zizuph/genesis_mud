inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("dagger");
   add_adj("steel");
   add_adj("long");
   set_short("long steel dagger");
   set_long("This is a plain, yet sharp looking dagger. It looks "+
   "like it is of average make.\n");
   set_hit(12);
   set_pen(14);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,72);
   add_prop(OBJ_I_VOLUME, 3600);
   add_prop(OBJ_I_WEIGHT, 3700);
}
