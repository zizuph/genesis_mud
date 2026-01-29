inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("tunic");
   set_adj("yellow");
   set_adj("dingy");
   set_long("This is a particularly large shirt " +
      "of sorts, yellow in color and rather dingy.  It " +
      "is of poor quality.\n");
   set_ac(1);
   set_am(({ 0, 0, 0 }));
   set_at(A_BODY | A_ARMS);
}
