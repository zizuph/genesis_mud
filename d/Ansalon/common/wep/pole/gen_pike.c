inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("pike");
    add_adj("steel");
    add_adj("long");
    set_short("long steel pike");
    set_long("This is a plain, yet long and sturdy pike. The blade "+
	"at the top looks sharp.\n");
    set_default_weapon(28,30,W_POLEARM, W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
