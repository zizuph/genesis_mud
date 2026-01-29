inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("helm");
   set_adj("bogman");
   set_adj("leather");
   set_long("This leather device is stylish and sheek! " +
      "Two leather flaps can be pulled down over the ears " +
      "for added protection, warmth, and style.  Chics " +
      "dig bogman!\n");
   set_ac(10);
   set_am(({ -4, -4, 8 }));
   set_at(A_HEAD);
}
