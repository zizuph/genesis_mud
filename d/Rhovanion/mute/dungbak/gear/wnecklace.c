inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("pendant");
   set_adj("disked");
   set_adj("gold");
   set_long("This necklace consists of a thin gold chain " +
      "with a solid gold disk attached.  The disk is over two " +
      "inches in diameter and nearly a half an inch thick.  It " +
      "bears the protruding imprint of a great, coiled wyrm " +
      "lying before four pillars and an altar.  It is a bit " +
      "heavy and is probably worth something to a collector of " +
      "jewelry and such.\n");
   set_ac(0);
   set_at(A_NECK);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME,  300);
   add_prop(OBJ_I_VALUE,  2000);
}
