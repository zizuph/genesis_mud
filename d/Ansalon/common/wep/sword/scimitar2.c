#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name(({"sword","scimitar"}));
    set_short("black steel scimitar");
    set_long("A wicked looking curved sword. The steel is blackened as if it "+
	"had been burned.\n");
    set_adj(({"black","steel", "curved"}));
    set_default_weapon(35, 30, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
