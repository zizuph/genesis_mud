inherit "/std/leftover";

#include "stdproperties.h"

void
create_leftover()
{
    set_name("skin");
    set_adj("fox");;
    set_long("A foxes hide.\n");
  
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,400);
    add_prop(OBJ_I_VALUE,200);
}
