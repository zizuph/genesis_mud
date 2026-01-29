inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("plates");
   set_adj("shoulder");
   set_adj("dented");
   set_long("This is a pair of metal plates attached by a pair of " +
      "leather straps designed to be worn over the shoulders and " +
      "upper arms.  They look pretty old and dented right now.\n");
   set_ac(12);
   set_am(({ -2, 2, 0 }));
   set_condition(2);
   set_at(A_ARMS);
   add_prop(OBJ_I_WEIGHT, 4000);
   add_prop(OBJ_I_VOLUME, 2000);
}
