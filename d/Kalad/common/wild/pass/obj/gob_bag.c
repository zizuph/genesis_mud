inherit "/std/receptacle";

#include <stdproperties.h>

/* by Antharanos */
// short desc fixed by Fysix, Oct 1997

void
create_receptacle()
{
   set_name("bag");
   set_adj(({"small", "filthy", "leather"}));
   set_short("small filthy leather bag");
   set_pshort("small filthy leather bags");
   set_long("A small container made of hardened leather, it smells of "+
      "half-rotted meat.\n");
   add_prop(CONT_I_WEIGHT,500);
   add_prop(CONT_I_MAX_WEIGHT,35500);
   add_prop(CONT_I_VOLUME,1500);
   add_prop(CONT_I_MAX_VOLUME,51500);
   add_prop(OBJ_I_VALUE,240);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(CONT_M_NO_REM,1);
}
