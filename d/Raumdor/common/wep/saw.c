#pragma strict_types
#include "defs.h"
inherit "/std/weapon";


public void
create_weapon()
{
    set_name("saw");
    set_adj("wood");
    set_short("wood saw");
    set_long("This saw has a wide serrated blade used most often to cut planks of wood.\n");
    
    set_default_weapon(5, 5, W_SWORD, W_SLASH, W_ANYH, 0);

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VALUE, SILVER_VALUE);
}
