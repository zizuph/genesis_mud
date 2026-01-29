#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"sword","shortsword"}));
    set_adj("polished");
    add_adj("steel");
    set_short("polished shortsword");
    set_long("A polished steel shortsword, weapons " +
      "typically used by sentries of Kalaman.\n");
    set_default_weapon(26,20,W_SWORD,W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
