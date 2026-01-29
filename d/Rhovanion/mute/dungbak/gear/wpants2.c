inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("leggings");
   set_adj("chain");
   set_adj("plated");
   set_short("the plated chain leggings");
   set_long("This is a pair of chainmail leggings accompanied " +
      "by a leather belt to keep them up with plates covering " +
      "the thighs in the front as well as the shins.  For " +
      "relatively lightweight armour it gives decent " +
      "protection.\n");
   set_ac(25);
   set_am(({ 0, 0, 0 }));
   set_at(A_LEGS);
}
