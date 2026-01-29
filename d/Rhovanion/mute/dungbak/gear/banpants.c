inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("pants");
   set_adj("leather");
   set_adj("black");
   set_long("This is a pair of black leather pants with black leather ties fringing " +
      "the sides allowing the wearer to tighten them for an exact, " +
      "comfort fit.  A black leather belt has already been thread " +
      "through the ties at the waist completing the exquisite look " +
      "of these pants.\n");
   set_ac(5);
   set_am(({ 0, -2, 2 }));
   set_at(A_LEGS);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 800);
   add_prop(OBJ_I_VALUE,  500);
}
