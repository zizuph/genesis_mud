inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("boots");
   set_adj("leather");
   set_adj("horned");
   set_long("This is a large pair of boots constructed of stiff, dark " +
      "leather and reinforced externally with dark steel, vertical " +
      "strips of metal circling the shin area each an inch or two " +
      "apart.  Odd, horns protrude from the very top of the boot " +
      "below the knee.\n");
   set_ac(10);
   set_at(A_FEET);
}
