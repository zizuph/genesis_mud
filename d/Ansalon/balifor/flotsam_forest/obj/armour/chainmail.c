inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 33

void
create_armour()
{
   set_name("armour");
   add_name("chainmail");
   set_pname("armours");
   
   set_adj("dwarven");
   add_adj("high");
   
   set_short("high dwarven chainmail");
   set_pshort("high dwarven chainmails");
   set_long("This is an exceptionally made, if not somewhat " +
      "grimy, set of dwarven chainmail. Made of the finest steel " +
      "and by skilled hands, it does not surprise you that it " +
      "offers fine protection.\n");
   
   set_ac(ARMOUR_CLASS);
   set_at(A_BODY);
   
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 2500);
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
