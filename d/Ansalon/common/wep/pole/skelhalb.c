inherit "/std/weapon";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("spear");
    set_adj(({"long","jagged"}));
    set_short("long jagged spear");
    set_long("As you look at the long jagged spear, you can't help "+
	"shivering at the barbs on the blade. The mere sight of them " +
	"leaves you very thankful that they are not embedded in " +
	"your flesh.\n");
    set_default_weapon(35, 35, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
