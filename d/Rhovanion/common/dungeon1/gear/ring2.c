inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("ring");
   set_adj("gold");
   set_adj("jade-studded");
   set_long("This solid gold ring is studded with ten small " +
      "oval jade stones that are remarkably luscious and green. " +
      "This item looks expensive.\n");
   set_ac(0);
   set_am(({ 0, 0, 0 }));
   set_at(A_ANY_FINGER);
   add_prop(OBJ_I_VALUE, 1100);
   add_prop(OBJ_I_WEIGHT, 650);
   add_prop(OBJ_I_VOLUME, 225);
}
