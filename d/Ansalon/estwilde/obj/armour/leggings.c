inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
   set_name("leggings");
   set_ac(20);
   set_at(A_LEGS);
   set_am( ({ 5, -3, -2 }) );
   set_adj("iron");
   set_short("pair of iron leggings");
   set_pshort("pairs of iron leggings");
   set_long("A pair of iron leggings. They are somewhat " +
      "battered and scratched, but seem to offer decent leg " +
      "protection.\n");
   add_prop(OBJ_I_VOLUME, 450);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}

