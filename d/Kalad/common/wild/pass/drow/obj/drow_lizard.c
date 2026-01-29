inherit "/std/food";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_food()
{
   set_name("lizard");
   set_adj("roasted");
   set_short("roasted lizard");
   set_pshort("roasted lizards");
   set_long("A small lizard, roughly the size of a human head that has "+
      "been roasted to a succulent golden-brown color.\n");
   add_prop(OBJ_I_WEIGHT,150);
   add_prop(OBJ_I_VOLUME,150);
   set_amount(150);
}
