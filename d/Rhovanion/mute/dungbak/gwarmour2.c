inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("helm");
   set_adj("battered");
   set_long("This small helm covers only the top of the head " +
      "and is not in good shape.  It appears as if it's been " +
      "through quite a few battles.\n");
   set_condition(2);
   set_ac(12);
   set_at(A_HEAD);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 1100);
}
