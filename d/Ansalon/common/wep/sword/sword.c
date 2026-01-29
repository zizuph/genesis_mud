#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("sword");
    set_adj(({"narrow","sharp"}));
    set_short("narrow sharp sword");
    set_long("The narrow sword looks sharp and deadly. The hilt is bound " +
        "in strips of leather and provides a good grip.\n");
    set_default_weapon(30,32,W_SWORD,W_IMPALE | W_SLASH, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}

