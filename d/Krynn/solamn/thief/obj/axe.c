/* created by Aridor, 03/17/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("axe");
    set_adj("ornamental");
    set_short("ornamental axe");
    set_long("It's a finely crafted axe, made from gold. " +
	     "There are many ornaments and carvings on the " +
	     "hilt, but you cannot make any sense of them.\n");
    set_default_weapon(14, 18, W_AXE, W_SLASH | W_BLUDGEON, W_ANYH);
    set_likely_break(11);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 4000);
}

