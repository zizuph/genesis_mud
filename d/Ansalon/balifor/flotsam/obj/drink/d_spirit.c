inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
   set_soft_amount(200);
   set_alco_amount(49);
   set_name(({"spirit","_flotsam_c_spirit_"}));
   set_adj("dwarven");
   set_short("shot of dwarven spirits");
   set_pshort("shots of dwarven spirits");
   set_long("This drink was brewed by the evil Zhakar dwarves, " +
      "and would have been imported at great expense. This drink " +
      "is reknowned along the Bloodsea coastline for its potency, " +
      "so for those weak of stomach, this is one spirit you " +
      "should not try! \n");
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 200);
}
