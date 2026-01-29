inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();
   set_name("dagger");
   set_adj("slim");
   add_adj("sharp");
   set_short("sharp slim dagger");
   set_long("this dagger is slim, and sharp. It looks as if it can "+ 
   "punch through the toughest of armours, makeing it perfect for "+ 
   "backstabbing.\n");
   set_hit(14);
   set_pen(15);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,50);
   add_prop(OBJ_I_VALUE,200);
}
