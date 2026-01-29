inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
   set_name("mask");
   set_adj("skull");
   set_ac(9);
   set_at(A_HEAD);
   set_am( ({ -5, 0, 5 }) );
   set_long("This hideous, white goat-skull mask covers the " +
      "front half of the wearers face. Horns curl around from " +
      "its sides.\n");
   set_short("skull mask");
   add_prop(OBJ_I_VOLUME, 150);
}
