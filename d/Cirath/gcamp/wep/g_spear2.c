inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("shortspear");
   add_name("spear");
   set_adj("one-handed");
   add_adj("iron-headed");
   set_long("A shaft of black wood topped by a dull black iron head "
   	+"makes up this simple weapon.  While the tip is just iron, "
   	+"it looks to be very sharp and able to penetrate flesh very "
   	+"easily.  As opposed to most spears, this one is fairly short "
   	+"and looks to be designed for one handed use.\n");
   set_hit(30);
   set_pen(31);
   set_wt(W_SPEAR);
   set_dt(W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,1500);
}

