inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("shirt");
   set_adj("chainmail");
   set_long("This is a simple chainmail shirt of " +
      "the lowest quality.  It still looks pretty protective just " +
      "the same.\n");
   set_ac(12);
   set_am(({ 0, 0, 0 }));
   set_at(A_BODY | A_ARMS);
}
