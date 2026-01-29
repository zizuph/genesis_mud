inherit "/std/object.c";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("gem");
   set_adj("light");
   set_short("gem of light");
   set_long("A clear gem of the finest quality. From its center, a strong "+
      "and pure light shines forth.\n");
   add_prop(OBJ_I_VALUE,3456);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_LIGHT,1);
   add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );
   add_prop(OBJ_M_NO_SELL,1);
}
