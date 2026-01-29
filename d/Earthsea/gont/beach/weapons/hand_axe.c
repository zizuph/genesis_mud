#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("axe");
    set_pname("axes");
    set_adj(({"iron", "hand"}));
    set_short("iron hand axe");
    set_pshort("iron hand axes");
    set_long("A small axe, wielded in one hand, " +
        "with a sharp axehead made from iron.\n");
    set_hit(9); 
    set_pen(15); 
    set_default_weapon(9, 25, W_AXE, W_BLUDGEON|W_SLASH, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, 200);
}
