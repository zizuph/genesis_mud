inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("ring");
   set_adj("nose");
   set_adj("golden");
   set_long("This is a small one inch diameter nose ring that " +
      "though appearing to be gold is probably just plated or is " +
      "some weird alloy.  Just the same it's still probably worth " +
      "a bit seeing how nose rings are in such high demand these " +
      "days.\n");
   set_ac(1);
   set_am(({ 0, 0, 0 }));
   set_at(A_HEAD);
   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_VALUE,  400);
}
