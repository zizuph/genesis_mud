#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("sword");
    add_name("longsword");
    add_adj("steel");
    add_adj("sturdy");
    set_short("sturdy steel longsword");
    set_long("This is a plain, steel sword of average make. Its hilt "+
      "is unadorned, yet the blade looks strong and sturdy.\n");
    set_default_weapon(30,30,W_SWORD,W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
