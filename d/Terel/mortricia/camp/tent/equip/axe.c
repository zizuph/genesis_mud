/* A simple axe. Mortricia 920729 */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("axe");
    set_short("simple axe");
    set_long("It's a simple axe, usually used by less fortunate " +
	     "dwarves.\n");
    set_adj("simple");
    set_hit(15);
    set_pen(15);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 1000);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
}
