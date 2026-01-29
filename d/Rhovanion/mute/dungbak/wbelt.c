inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("belt");
   set_adj("leather");
   set_adj("horn-studded");
   set_long("This fine, dark leather belt is studded with " +
      "small, off-white reptilian horns all around it spaced " +
      "about two inches apart each.\n");
   set_ac(1);
   set_at(A_WAIST);
}
