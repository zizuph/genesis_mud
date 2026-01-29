inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("leggings");
   set_adj("leather");
   set_adj("light");
   set_long("This is an oversized pair of light leather " +
      "leggings with ties by the waist and along the sides " +
      "of the legs and of poor quality.\n");
   set_ac(2);
   set_am(({ 0, 0, 0 }));
   set_at(A_LEGS);
}
