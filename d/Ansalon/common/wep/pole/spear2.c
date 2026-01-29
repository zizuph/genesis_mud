inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("spear");
    set_adj("long");
    set_short("long spear");
    set_long("This long spear is fairly primitive, but " +
	"from the trophies attached to it, you would say its " +
	"late owner found it effective enough for pillaging " +
	"and raiding.\n");
    set_default_weapon(28, 20, W_POLEARM, W_IMPALE, W_BOTH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
