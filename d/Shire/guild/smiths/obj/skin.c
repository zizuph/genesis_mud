inherit "/std/leftover";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"

void
create_leftover() {

   set_name("skin");
   set_adj("wolf");

   set_long("A wolfs hide.\n");

   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,300);
   add_prop(OBJ_I_VALUE,200);
}

