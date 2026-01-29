inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("robe");
   set_adj("scaled");
   set_adj("leather");
   set_long("The vital areas of this long, red robe are " +
      "covered with small, extremely hard leather scales. " +
      "Each scale is well-lacquered and bears the imprint " +
      "of some sort of long, snake-like beast in its center. " +
      "The inside of the robe is lined with a thin layer of " +
      "padding to further its protective ability.  Despite its " +
      "accoutrements this garment is rather light.\n");
   set_ac(15);
   set_am(({ -5, 0, 5 }));
   set_at(A_ROBE | A_ARMS);
   add_prop(OBJ_I_WEIGHT, 4500);
   add_prop(OBJ_I_VOLUME, 8500);
}
