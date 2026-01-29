inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
   set_soft_amount(50);
   set_alco_amount(200);
   set_name(({"rum","bottle"}));
   set_adj("sailors");
   set_short("bottle of sailors rum");
   set_pshort("bottles of sailors rum");
   set_long("Commonly known as 'fighting juice', rum is the beloved " +
      "drink of choice of all sailors from the Turbidus Ocean to the " +
      "Bloodsea of Istar. This rum is reknowned for its potency, " +
      "so for those weak of stomach, this is one spirit you " +
      "should not try! \n");
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
