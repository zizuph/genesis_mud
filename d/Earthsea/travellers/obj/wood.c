#pragma strict_types

inherit "/std/object.c";

#include "../guild.h"
#include <stdproperties.h>

public void
create_object()
{
    set_name("wood");
    add_name(CARVE_OBJECT_ID);

    set_adj("piece of");
    add_adj("fresh");
    add_adj("soft");
  
    set_long("A good piece of wood to make carvings from.\n");

    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VALUE, 1);
}
