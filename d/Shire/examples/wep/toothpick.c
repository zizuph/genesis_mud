inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
   set_name("toothpick");
   set_short("small wooden toothpick");
   set_long("A sharp, nasty, pointy toothpick.\n");
   set_adj(({"small", "wooden"}));
   set_hit(13);
   set_pen(6);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,  1200 + random(50));
   add_prop(OBJ_I_WEIGHT, 2000 + random(25));
   add_prop(OBJ_I_VOLUME, 2000 + random(100));
}
