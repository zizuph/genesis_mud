inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
   set_name("helmet");
   set_ac(20);
   set_at(A_HEAD);
   set_am( ({ -5, 0, 5 }) );
   set_adj("horned");
   set_long("This is the typical headgear of a dwarf " +
      "from the hills... an impressive steel helmet with " +
      "two stubby horns protruding from its sides.\n");
   add_prop(OBJ_I_VOLUME, 150);
}
