inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
   set_name("robe");
   set_ac(9);
   set_at(A_ROBE);
   add_adj("black");
   set_short("black robe");
   set_long("This thick black robe is typical of the priests of Chemosh. " +
      "Its material is coarse yet fairly light, and offers fair " +
      "protection from the elements. \n");
   add_prop(OBJ_I_VOLUME, 4750);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
}

