inherit "/std/armour";
#include "/sys/wa_types.h"

#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("jacket");
   set_adj("leather");
   set_adj("studded");
   set_long("This open faced jacket is made of hardened leather " +
      "and is studded with small copper plates randomly over its surface. " +
      "It looks like it offers very little protection, but that's better than " +
      "nothing.\n");
   set_ac(6);
   set_am(({ -2, -1, 3 }));
   set_at(A_BODY);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 1850);
}
