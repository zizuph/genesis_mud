inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
   set_name("armour");
   add_name("platemail");
   add_name("plate");
   set_adj("bloodstained");
   add_adj("bone");
   set_short("bloodstained bone armour");
   set_ac(37);
   set_at(A_BODY);
   set_long("This is a set of bone armour, fashioned in " +
      "a likeness to platemail. It is stained with blood from " +
      "both fresh and old kills. It is typically worn by " +
      "the high priests of Chemosh.\n");
   add_prop(OBJ_I_VOLUME, 3040);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_BODY));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
}


