inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("halberd");
    add_adj("steel");
    add_adj("long");
    set_short("long steel halberd");
    set_long("This is a plain, yet long and sturdy halberd. The curved blade "+
	"at the top looks sharp and ready to shread flesh.\n");
    set_default_weapon(28,34,W_POLEARM,W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
