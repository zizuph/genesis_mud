inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
   set_soft_amount(150);
   set_alco_amount(10);
   set_name("brew");
   set_adj("stolen");
   set_short("stolen brew");
   set_pshort("stolen brews");
   set_long("This ale of unknown make or origin was likely stolen " +
      "from a merchant ship sailing the Turbidus or Courrain Ocean. " +
      "While of unknown make, it is mighty tasty!\n");
   add_prop(OBJ_I_WEIGHT, 150);
   add_prop(OBJ_I_VOLUME, 150);
}
