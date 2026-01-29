inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("axe");
    set_adj("notched");
    set_long("This is an old, two-handed battleaxe that looks like it has seen better " + 
      "times. It has notches down its wooden grip, signifying the number of enemies " +
	"the owner has slain with it.\n");
    set_short("notched axe");
    set_default_weapon(20,27,W_AXE,W_SLASH, W_BOTH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
