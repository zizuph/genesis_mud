inherit "/std/leftover";

#include "stdproperties.h"

void
create_leftover()
{
    set_name("skin");
    set_adj("wolf");;
    set_long("A wolf's hide.\n");
  
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,200);
}
