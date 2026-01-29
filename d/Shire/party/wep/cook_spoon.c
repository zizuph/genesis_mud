inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
   ::create_weapon();
   set_name("spoon");
   set_short("wooden spoon");
   set_long("This is a small wooden spoon which you could beat "+
      "someone over the head with if you got mad enough at them.\n");
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   set_hit(7);
   set_pen(10);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(7,10));
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(10,W_CLUB));
   add_prop(OBJ_I_VOLUME,query_prop(OBJ_I_WEIGHT)/5);
}
