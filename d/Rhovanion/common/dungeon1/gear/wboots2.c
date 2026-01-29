inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("boots");
   set_adj("leather");
   set_adj("dark");
   set_long("This is a pair of large, dark leather boots. " +
      "They have ties at the top and are of poor quality.\n");
   set_ac(1);
   set_am(({ 0, 0, 0 }));
   set_at(A_FEET);
}
