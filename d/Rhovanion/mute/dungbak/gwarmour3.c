inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("shirt");
   set_adj("scaled");
   set_adj("corroded");
   set_long("This steel alloy scaled armour covers the chest " +
      "of its wearer, but is presently pretty beat up and in a " +
      "sad state of disrepair.\n");
   set_condition(1);
   set_ac(15);
   set_at(A_BODY);
   add_prop(OBJ_I_WEIGHT, 5000);
   add_prop(OBJ_I_VOLUME, 3700);
}
