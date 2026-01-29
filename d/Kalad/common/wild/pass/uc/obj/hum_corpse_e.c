inherit "/std/container";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_container()
{
   set_name("corpse");
   set_short("corpse of a human");
   set_long("The pitiful, devoured, remnants of a human.\n");
   add_prop(CONT_I_WEIGHT,70000);
   add_prop(CONT_I_MAX_WEIGHT,170000);
   add_prop(CONT_I_VOLUME,70000);
   add_prop(CONT_I_MAX_VOLUME,170000);
   add_prop(OBJ_M_NO_SELL,1);
}
