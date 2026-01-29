#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("cutlass");
    add_name("sword");
    set_adj("narrow");
    set_short("narrow cutlass");
    set_long("The narrow slashing sword known as the cutlass is a favorite "+
        "among sailors. This one appears to be well-made.\n");
    set_default_weapon(29, 22, W_SWORD, W_SLASH, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
