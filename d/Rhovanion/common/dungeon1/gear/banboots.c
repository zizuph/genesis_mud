inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("boots");
   set_adj("leather");
   set_adj("black");
   set_long("This is a pair of black leather boots with black " +
      "leather ties fringing the sides allowing the wearer to " +
      "tighten them for an exact, comfort fit.  They are well " +
      "made and well kept and look pretty cool, too.\n");
   set_ac(4);
   set_am(({ 0, -1, 1 }));
   set_at(A_FEET);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VOLUME, 220);
   add_prop(OBJ_I_VALUE, 225);
}
