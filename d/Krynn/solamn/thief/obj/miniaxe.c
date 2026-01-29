/* created by Aridor, 03/23/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("axe");
    set_adj("small");
    set_short("small axe");
    set_long("It's a small axe, but which might just give you " +
	     "the edge in a fight.\n");
    set_default_weapon(8, 13, W_AXE, W_BLUDGEON | W_SLASH, W_ANYH);
    set_likely_break(11);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 800);
}

