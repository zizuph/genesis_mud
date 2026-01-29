#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("axe");
    set_adj("hefty");
    add_adj("broad-bladed");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("hefty broad-bladed axe");
    set_long("A heavy-looking axe with an unusually broad axe-blade.\n");
    set_hit(22);
    set_pen(29);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE,720);
    add_prop(OBJ_I_WEIGHT,12000);
    add_prop(OBJ_I_VOLUME,8000);
}
