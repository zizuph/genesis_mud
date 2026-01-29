inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("lance");
    set_adj("steel");
    add_adj("great");
    set_short("great steel lance");
    set_long("This long steel weapon is of impressive make. You " +
	"would imagine it would be carried by a skilled warrior " +
	"on at least a heavy warhorse.\n");
    set_default_weapon(32,26,W_POLEARM,W_IMPALE, W_BOTH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
