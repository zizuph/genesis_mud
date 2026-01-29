inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name(({"sword","shortsword"}));
    set_adj("polished");
    add_adj("steel");
    set_short("polished shortsword");
    set_long("A polished steel shortsword, weapons " +
      "typically used by sentries of Kalaman.\n");
    set_default_weapon(26,20,W_SWORD,W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 3700);
}
