inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("fine");
   add_adj("black");
   set_long("A long full robe, colored the deepest ebony. Upon it are "+
      "several encryptic runes, the meanings of which are lost to you.\n");
   set_ac(2);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,1200);
   add_prop(OBJ_I_VOLUME,2500);
   add_prop(OBJ_I_WEIGHT,2500);
}
