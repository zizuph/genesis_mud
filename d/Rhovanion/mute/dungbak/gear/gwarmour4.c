inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("leggings");
   set_adj("goat skin");
   set_long("This is a pair of goat skin leggings that, " +
      "despite their age, still look pretty warm.\n");
   set_ac(5);
   set_am(({ -2, -1, 3 }));
   set_at(A_LEGS);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 4000);
}
