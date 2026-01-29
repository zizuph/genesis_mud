inherit "/std/object.c";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("water");
   set_adj("large amount of");
   set_long("Cold, crystal-clear water that sparkles in the light.\n");
   add_prop(OBJ_I_WEIGHT,7500);
   add_prop(OBJ_I_VOLUME,7500);
}
