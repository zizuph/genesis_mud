inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("scythe");
   set_adj("bloodied");
   set_short("bloodied scythe");
   set_long("A curved blade attached to a long blackened pole, " +
      "this scythe looks like it has been used to reap souls, not " +
      "crops. \n");
   set_default_weapon(20,31,W_POLEARM,W_SLASH,W_BOTH);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_WEIGHT, 2500);
}
