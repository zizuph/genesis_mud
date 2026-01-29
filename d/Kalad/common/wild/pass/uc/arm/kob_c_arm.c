inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("armour");
   set_adj("filthy");
   add_adj("chain");
   set_long("A suit of grey chain mail that is presently covered in "+
      "giant splotches of fecal matter, truly nauseating.\n");
   set_ac(25);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,750);
   add_prop(OBJ_I_WEIGHT, 10000);
   add_prop(OBJ_I_VOLUME,4000);
}
