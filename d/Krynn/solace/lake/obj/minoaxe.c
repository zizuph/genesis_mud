/* created by Splunge 1/15/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("axe");
    set_short("heavy double bladed axe");
    set_pshort("heavy double bladed axes");
    set_adj("heavy");
    add_adj("double");
    add_adj("bladed");
    set_long("This large double bladed axe looks like it has seen " +
	     "extensive use, but it still has a fine edge on it. The handle "+
	     "contains many notches in it, each one representing a fallen " +
	     "foe.\n");
    set_default_weapon(29, 39, W_AXE, W_SLASH | W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 5500);
    add_prop(OBJ_I_WEIGHT, 30000);
}
