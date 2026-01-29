inherit "/std/armour";

#include "default.h"

void
create_armour()
{
   set_name("helmet");
   set_short("silver helmet");
   
   set_adj("silver");
   set_long("This is a large helmet covered with shining silver plates. "+
      "The plates are woven together to form a thick silver mesh. The mest "+
      "rests atop and between thick leather hides and strings, "+
      "making for a comfortable, yet decorative and protective helmet.\n");
   
   
   set_ac(14);
   set_at(A_HEAD);
   set_am(({ -1, -1, 2 }));
   
   add_prop(OBJ_I_VALUE, 195);
   add_prop(OBJ_I_WEIGHT, 612);
   add_prop(OBJ_I_VOLUME, 410);
}
