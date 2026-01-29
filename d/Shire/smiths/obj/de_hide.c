inherit "/std/leftover";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"

void
create_leftover() {

   set_name("hide");
   set_adj("deer");

   set_long("A deer's hide.\n");

   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,300);
   add_prop(OBJ_I_VALUE,200);
}

