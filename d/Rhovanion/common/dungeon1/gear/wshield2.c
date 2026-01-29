inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("shield");
   set_adj("steel");
   set_adj("studded");
   set_long("This steel shield is rimmed with metal " +
      "studs all around the perimeter of its front. " +
      "It bears the scars of many battles.\n");
   set_ac(22);
   set_am(({ 0, 0, 0 }));
   set_at(A_SHIELD);
}
