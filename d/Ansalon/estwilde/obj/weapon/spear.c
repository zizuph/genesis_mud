inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("spear");
    set_adj("long");
    set_short("long spear");
    set_pshort("long spears");
    set_long("This long spear is fairly primitive, but " +
      "from the trophies attached to it, you would say its " +
      "late owner found it effective enough for pillaging " +
      "and raiding.\n");
    set_default_weapon(28, 20, W_POLEARM, W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 10000);
}
