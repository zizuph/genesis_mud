inherit "/std/food";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_food()
{
   set_name("mushroom");
   set_adj("fresh");
   set_short("fresh mushroom");
   set_pshort("fresh mushrooms");
   set_long("Delicate and soft mushrooms, grown in the caves of Underhome.\n");
   add_prop(OBJ_I_WEIGHT,30);
   add_prop(OBJ_I_VOLUME,30);
   set_amount(30);
}
