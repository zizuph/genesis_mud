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
    set_adj("short");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("short cutlass");
    set_long("The cutlass is a weapon often prized " +
	"by pirates and sailors. This one is " +
	"short and heavy, but has a sharp edge, making it dangerous " +
	"in the right, or wrong, hands.\n");
    set_default_weapon(20, 27, W_SWORD, W_SLASH, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
