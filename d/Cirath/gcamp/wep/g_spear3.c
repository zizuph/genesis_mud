inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("spear");
   set_adj("long");
   add_adj("stiletto-tipped");
   set_long("Crafted from a long pole of agafari wood and topped "
   	+"with a thin iron spike, this weapon looks to be able to "
   	+"easily pierce armours and flesh.  Though very strong, "
   	+"it still manages to retain its light weight so that it is "
   	+"extremely fast weapon to use.\n");
   set_hit(30);
   set_pen(44);
   set_wt(W_SPEAR);
   set_dt(W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,1500);
}
