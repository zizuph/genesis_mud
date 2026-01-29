inherit "/std/receptacle";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_receptacle()
{
   set_name("chest");
   set_adj("large");
   add_adj("adamantine");
   set_long("A large container fashioned from enduring adamantine. If you "+
      "wished to, you could leave any equipment here that other, less fortunate "+
      "members of House Noquar would be able to use when next they wake.\n");
   add_prop(CONT_I_WEIGHT,20000);
   add_prop(CONT_I_MAX_WEIGHT,220000);
   add_prop(CONT_I_VOLUME,20000);
   add_prop(CONT_I_MAX_VOLUME,220000);
   add_prop(OBJ_I_VALUE,1000);
   add_prop(OBJ_M_NO_GET,"The large adamantine chest is firmly stuck to the "+
      "ground. You fail in your attempt to remove it.\n");
}
