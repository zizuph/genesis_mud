#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("sword");
    set_short("two handed sword");
    set_long("This is quite an impressive sword. The blade is a full meter "+
	"and has not lost it's sharpness over the years. Like " +
	"everything else here, it has lost it's shimmer, and seems to " +
	"have been scorched by a fire.\n");
    set_adj("two handed");
    set_default_weapon(35, 40, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
