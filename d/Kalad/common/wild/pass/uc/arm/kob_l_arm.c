inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("armour");
   set_adj("filthy");
   add_adj("leather");
   set_long("A suit of leather armour that is covered in giant splotches "+
      "here and there with feces, truly disgusting.\n");
   set_ac(8);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,600);
   add_prop(OBJ_I_WEIGHT, 4000);
   add_prop(OBJ_I_VOLUME,2000);
}
