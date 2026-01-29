inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
   ::create_weapon();
   set_name("spear");
   set_short("small spear");
   set_long("A typical spear that can usually be found in the "+
      "hands of the local hobbit militia.\n");
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   set_hands(W_BOTH);
   set_hit(10);
   set_pen(15);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10,15));
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(15,W_POLEARM));
   add_prop(OBJ_I_VOLUME,query_prop(OBJ_I_WEIGHT)/5);
}
