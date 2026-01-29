#pragma strict_types
#include "defs.h"
inherit "/std/weapon";


public void
create_weapon()
{
    set_name(({"trowel", "_masonry_trowel"}));
    set_adj("masonry");
    set_short("masonry trowel");
    set_long("This hand trowel is flat with a pointed nose, excellent for " +
      "buttering mortar on bricks.\n");
    
    set_default_weapon(1, 1, W_KNIFE, W_IMPALE, W_ANYH, 0);

    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE, COPPER_VALUE * 8);
}
