inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("buckler");
   add_name("shield");
   set_adj("leather");
   set_adj("steel plated");
   set_long("This piece of armour consists of a " +
      "hardened piece of leather covered with strips of " +
      "steel for added protection and strapped to your " +
      "outer forearm to aid in blocking while leaving " +
      "your hands free to wield weapons.\n");
   set_ac(23);
   set_am(({ -3, 2, 1 }));
   set_at(A_R_ARM);
}
