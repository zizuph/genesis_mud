inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("shield");
   set_adj("wooden");
   set_adj("hard");
   set_long("This small shield is made of a very " +
      "dark color and dark stained wood.  It looks sturdy.\n");
   set_ac(15);
   set_am(({ 0, 0, 0 }));
   set_at(A_SHIELD);
}
