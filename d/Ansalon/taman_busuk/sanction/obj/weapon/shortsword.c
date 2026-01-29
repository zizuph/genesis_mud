inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name(({"sword","shortsword"}));
    set_adj("dented");
    add_adj("steel");
    add_adj("metal");
    set_short("dented shortsword");
    set_long("A dented steel shortsword, most likely from a stock of " +
             "weapons of last resort.\n");
    set_default_weapon(26,20,W_SWORD,W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 3700);
}
