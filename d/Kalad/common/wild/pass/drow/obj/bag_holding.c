inherit "/std/receptacle";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_receptacle()
{
   set_name("bag");
   set_adj("holding");
   set_short("bag of holding");
   set_pshort("bags of holding");
   set_long("A large bag sewn from silky-soft spider silk. An image of a "+
      "black widow spider has been sewn onto it.\n");
   add_prop(CONT_I_WEIGHT, 1000);
   add_prop(CONT_I_MAX_WEIGHT,126000);
   add_prop(CONT_I_VOLUME, 15000);
   add_prop(CONT_I_MAX_VOLUME,140000);
   add_prop(OBJ_I_VALUE,1722);
   set_keep();
   add_prop(CONT_I_REDUCE_WEIGHT,500);
   add_prop(CONT_I_REDUCE_VOLUME,500);
   add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );
}
